
// #include <stdio.h>
// #include <stdint.h>
#include <dlfcn.h>

#include "asylo_lib_bin/enc_calls_c.h"
#include "include/grpcpp/grpcpp.h"


extern "C"{
 namespace asylo { namespace test {
EncCallsClient* ecc;
    void ecc_init(const std::shared_ptr<::grpc::ChannelInterface> &channel){
    ecc = new EncCallsClient(channel);
    }
    void ecc_delete(){
    delete ecc;
    }
    
    unsigned long long int  _ZN14CServerBrowser6FilterEv_stub  (unsigned long long int a,unsigned long long int b, unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f) {
        return ecc->_ZN14CServerBrowser6FilterEv(a,b,c,d,e,f);
    }
    

    void populate_add(unsigned long long int a){
        ecc->populate_add(a);
    }
}}

extern "C" unsigned long long int base_add_junk;
unsigned long long int base_add_junk;
unsigned long long int base_add;



unsigned long long int mem_free_var = 556000;
extern "C" unsigned long long mem_free_stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f){
    return (*(unsigned long long int(*)(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e, unsigned long long int f))(mem_free_var + base_add))(a,b,c,d,e,f);
}



unsigned long long int mem_alloc_debug_var = 555720;
extern "C" unsigned long long mem_alloc_debug_stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f){
    return (*(unsigned long long int(*)(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e, unsigned long long int f))(mem_alloc_debug_var + base_add))(a,b,c,d,e,f);
}



unsigned long long int str_comp_var = 567763;
extern "C" unsigned long long str_comp_stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f){
    return (*(unsigned long long int(*)(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e, unsigned long long int f))(str_comp_var + base_add))(a,b,c,d,e,f);
}



unsigned long long int str_comp_num_var = 567800;
extern "C" unsigned long long str_comp_num_stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f){
    return (*(unsigned long long int(*)(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e, unsigned long long int f))(str_comp_num_var + base_add))(a,b,c,d,e,f);
}



unsigned long long int str_find_nocase_var = 568169;
extern "C" unsigned long long str_find_nocase_stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f){
    return (*(unsigned long long int(*)(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e, unsigned long long int f))(str_find_nocase_var + base_add))(a,b,c,d,e,f);
}



unsigned long long int str_comp_nocase_var = 567680;
extern "C" unsigned long long str_comp_nocase_stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f){
    return (*(unsigned long long int(*)(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e, unsigned long long int f))(str_comp_nocase_var + base_add))(a,b,c,d,e,f);
}



extern "C" unsigned long long fct_ptr_stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d, unsigned long long int e,unsigned long long int f, unsigned long long int(*fct_ptr)(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int)){
    return (*fct_ptr)(a,b,c,d,e,f);
}



unsigned long long int _Z3maxIiET_S0_S0__var = 205662;
extern "C" unsigned long long _Z3maxIiET_S0_S0__stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f){
    return (*(unsigned long long int(*)(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e, unsigned long long int f))(_Z3maxIiET_S0_S0__var + base_add))(a,b,c,d,e,f);
}



unsigned long long int  (*rand_ptr)(unsigned long long int, unsigned long long int ,unsigned long long int , unsigned long long int,unsigned long long int ,unsigned long long int  ) = NULL;

void resolv_func_name(){
    rand_ptr = dlsym(RTLD_NEXT, "rand");
}

extern int init_enclave();


unsigned long long int dispatcher (unsigned long long int a,unsigned long long int b, unsigned long long int c, unsigned long long int d, unsigned long long int e,unsigned long long int f){

    if ( !rand_ptr ) {
        resolv_func_name();
        init_enclave();
    }
    register long id asm("r11");
    
    if (id == 1095053878){

        if (!base_add){
            base_add = base_add_junk - 590444;
            asylo::test::populate_add(base_add);
        }
        id = -1;
        return asylo::test::_ZN14CServerBrowser6FilterEv_stub(a,b,c,d,e,f);
    }
    
    else {
        return (*rand_ptr)(a,b,c,d,e,f);
    }
}


}