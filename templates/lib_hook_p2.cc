
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
    {% for enc_func in enc_funcs %}
    unsigned long long int  {{enc_func[1]}}_stub  (unsigned long long int a,unsigned long long int b, unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f) {
        return ecc->{{enc_func[1]}}(a,b,c,d,e,f);
    }
    {% endfor %}


}}

extern "C" unsigned long long int base_add_junk;
unsigned long long int base_add_junk;
unsigned long long int base_add;

{% for host_func in host_funcs %}
{% if host_func.value != 0 %}
unsigned long long int {{host_func.name}}_var = {{host_func.value}};
extern "C" unsigned long long {{host_func.name}}_stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f){
    return (*(unsigned long long int(*)(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d,unsigned long long int e, unsigned long long int f))({{host_func.name}}_var + base_add))(a,b,c,d,e,f);
}
{% else %}
extern "C" unsigned long long {{host_func.name}}_stub(unsigned long long int a,unsigned long long int b,unsigned long long int c, unsigned long long int d, unsigned long long int e,unsigned long long int f, unsigned long long int(*fct_ptr)(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int)){
    return (*fct_ptr)(a,b,c,d,e,f);
}
{% endif %}
{% endfor %}

unsigned long long int  (*{{funcname}}_ptr)(unsigned long long int, unsigned long long int ,unsigned long long int , unsigned long long int,unsigned long long int ,unsigned long long int  ) = NULL;

void resolv_func_name(){
    {{funcname}}_ptr = dlsym(RTLD_NEXT, "{{funcname}}");
}

extern int init_enclave();


unsigned long long int dispatcher (unsigned long long int a,unsigned long long int b, unsigned long long int c, unsigned long long int d, unsigned long long int e,unsigned long long int f){

    if ( !{{funcname}}_ptr ) {
        resolv_func_name();
        init_enclave();
    }
    register long id asm("r11");
    {% for enc_func in enc_funcs %}
    {%if loop.index != 1 %}else {% endif %}if (id == {{enc_func[0]}}){

        base_add = base_add_junk - {{enc_func[2]}};
        id = -1;
        return asylo::test::{{enc_func[1]}}_stub(a,b,c,d,e,f);
    }
    {% endfor %}
    else {
        return (*{{funcname}}_ptr)(a,b,c,d,e,f);

    }
}


}
