import capstone
import lief
import sys
import struct
import jinja2
import subprocess


def generate_lib_hook(hook_func, begin_id, host_funcs, binary):
    env = jinja2.Environment(loader=jinja2.PackageLoader('TEEShift', 'templates'))
    temp = env.get_template("lib_hook_p1.cc")
    enc_funcs = []
    i = 0
    for func in sys.argv[2].split(":"):
        enc_funcs.append([begin_id+i,func, binary.get_symbol(func).value - binary.imagebase])
        i += 1

    lib_hook_content= temp.render(funcname=hook_func.symbol.name, enc_funcs=enc_funcs)
    with open("generated/lib_hook_p1.cc", "w") as f :
        f.write(lib_hook_content)

    temp = env.get_template("lib_hook_p2.cc")
    lib_hook_content= temp.render(funcname=hook_func.symbol.name, enc_funcs=enc_funcs, host_funcs=host_funcs)
    with open("generated/lib_hook_p2.cc", "w") as f :
        f.write(lib_hook_content)


def generate_enc_calls_c():
    env = jinja2.Environment(loader=jinja2.PackageLoader('TEEShift', 'templates'))
    temp = env.get_template("enc_calls_c.h")
    enc_calls_c_content= temp.render(enc_funcs=sys.argv[2].split(":"))
    with open("generated/enc_calls_c.h", "w") as f :
        f.write(enc_calls_c_content)

def generate_enc_calls_s():
    env = jinja2.Environment(loader=jinja2.PackageLoader('TEEShift', 'templates'))
    temp = env.get_template("enc_calls_s.h")
    enc_calls_s_content= temp.render(enc_funcs=sys.argv[2].split(":"))
    with open("generated/enc_calls_s.h", "w") as f :
        f.write(enc_calls_s_content)

def generate_service_proto(hc):
    env = jinja2.Environment(loader=jinja2.PackageLoader('TEEShift', 'templates'))
    temp = env.get_template("service.proto")
    enc_calls_c_content= temp.render(enc_funcs=sys.argv[2].split(":"), host_funcs=[s.name for s in hc])
    with open("generated/service.proto", "w") as f :
        f.write(enc_calls_c_content)

def generate_host_calls_s(hc):
        env = jinja2.Environment(loader=jinja2.PackageLoader('TEEShift', 'templates'))
        temp = env.get_template("host_calls_s.h")
        with open("generated/host_calls_s.h", "w") as f :
            f.write(temp.render(host_funcs=[s.name for s in hc]))

def generate_host_calls_c(hc):
        env = jinja2.Environment(loader=jinja2.PackageLoader('TEEShift', 'templates'))
        temp = env.get_template("host_calls_c.cc")
        with open("generated/host_calls_c.cc", "w") as f :
            f.write(temp.render(host_funcs=[s.name for s in hc]))


def resolv_add_at(binary, add):
    for s in binary.symbols:
        if s.value == add :
            return s
    i = 0
    for rel in binary.pltgot_relocations:
        if (i+1)*sizeplt + binary.get_section(".plt").virtual_address == add:
            s = lief.ELF.Symbol()
            s.name = rel.symbol.name
            s.value = add
            return s
        i += 1
    return None


def insert_lab_back(cur, iter, lab, target):
    i = 0
    for ins in iter :
        while(cur[i][0:3] == "lab"):
            i+=1
        if(ins.address == target) :
            cur.insert(i,lab)
            return True
    return False


def generate_enc(binary):
    env = jinja2.Environment(loader=jinja2.PackageLoader('TEEShift', 'templates'))
    temp = env.get_template("enc.c")

    cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    cs.syntax = capstone.CS_OPT_SYNTAX_ATT

    host_calls = []

    for fn in sys.argv[2].split(":"):

        print("\t✜ Generating code for ", fn)
        symbol = binary.get_symbol(fn)
        print("\t• Symbol found ✔")
        body = bytes(binary.get_content_from_virtual_address(symbol.value,symbol.size))
        print("\t• Code read ✔")
        cur = []
        prepend = []

        general_off = [[0,0]]
        if ("--debug" in sys.argv):
            cur.append("int3")
            prepend = [0xcc]
            general_off[-1] = [0,1]

        local_host_calls = []
        to_be_patched_call = []
        to_be_patched_jump = []

        j_ctr = 0
        labels = []
        print("\t• Disassembling Code...")
        for ins in cs.disasm(body, symbol.value):

            for x,y  in labels :
                if ins.address == y:
                    cur.append(x +":")

            op = ins.op_str
            instr = ins.mnemonic
            if "call" in ins.mnemonic :
                try :
                    call_add = int(ins.op_str[2:],16)
                except :
                    reg = op[2:]
                    cur.append("mov %%%s, %%r15" % reg)
                    op = "fct_ptr"+fn + "_stub"
                    if "fct_ptr" not in local_host_calls:
                        local_host_calls.append("fct_ptr")
                    s = lief.ELF.Symbol()
                    s.name = "fct_ptr"
                    s.value = 0
                    if s.name not in [x.name for x in host_calls]:
                        host_calls.append(s)

                else:
                    s = resolv_add_at(binary, call_add)
                    print("\t\tCall detected to function : "+ s.name)
                    if s.name not in [x.name for x in host_calls]:
                        host_calls.append(s)

                    op = s.name+fn+"_stub"
                    if s.name not in local_host_calls:
                        local_host_calls.append(s.name)

            if "j" == ins.mnemonic[0]:
                abs = int(ins.op_str[2:],16)
                lab =  str(j_ctr)
                j_ctr += 1

                if(abs > ins.address):
                    labels.append((lab,abs))
                    op = lab+"f"
                else :
                    op += lab+"b"
                    insert_lab_back(cur,cs.disasm(body, symbol.value), lab, op)

            cur.append("%s\t%s" %(instr, op))


        content = temp.render(function_name=fn, fct_cont=cur, host_calls=local_host_calls)
        filenamec = "generated/enc_temp_"+fn+".c"
        filenameo = "generated/enc_temp_"+fn+".o"


        with open(filenamec, "w") as f :
            f.write(content)
        print("\t• C file generated  ✔")

        if subprocess.call(["/bin/gcc",filenamec, "-fpic", "-c", "-Os", "-o", filenameo]) :
            print("[-] Something went wrong during compilation of %s" % filenamec)
            sys.exit(-1)
        if "--save_temp" in sys.argv:
                subprocess.call(["/bin/mkdir", "temp/"])
                subprocess.call(["/bin/cp",filenamec, "temp/"+fn+".c"])
        subprocess.call(["/bin/rm",filenamec])
        print("\t• C File Compiled ✔")

    return host_calls




sizeplt = 16
plt_off =  int(sys.argv[3])
begin_id = 0x41453236
def main():
    print("[*] Loading the binary :" + sys.argv[1])
    binary = lief.ELF.parse(sys.argv[1])
    print("\t• Binary Loaded ✔")

    print("[*] Finding the PLT entry to Hook...")
    hook_func = binary.pltgot_relocations[plt_off]
    hook_func_plt = (plt_off+1)*sizeplt + binary.get_section(".plt").virtual_address

    print("\t• Function Name : " + hook_func.symbol.name)
    print("\t• Address : " + hex(hook_func.address))

    print("[*] Generating Enclave Calls handler...")
    generate_enc_calls_c()
    print("\t• Client side ✔")
    generate_enc_calls_s()
    print("\t• Server side ✔")

    print("[*] Generating Enclave code...")
    hc = generate_enc(binary)

    generate_host_calls_s(hc)
    generate_host_calls_c(hc)


    generate_service_proto(hc)

    generate_lib_hook(hook_func, begin_id, hc, binary);



    print("[*] Now patching the binary...")

    function_id = begin_id

    for x in  sys.argv[2].split(":"):
        f = binary.get_function_address(x)
        patch = [0x68] + [x for x in struct.pack("<I",function_id)]  + [0x41, 0x5b, 0x4c ,0x8d, 0x35, ] + [x for x in struct.pack("<I",-14&0xffffffff)] +[0xE9]
        patch += list(bytearray(struct.pack("<I", (hook_func_plt - f -  len(patch) - 4)&0xffffffff)))
        patch += [0xc3] * (binary.get_symbol(x).size-len(patch))
        binary.patch_address(f,patch)
        function_id += 1


    binary.write(sys.argv[1]+"_patched")



if __name__ == "__main__" :
    print("[+] Welcome to TEEShift")
    main()
