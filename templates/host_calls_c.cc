#include <memory>
#include <string>
#include <type_traits>
#include "asylo_lib_bin/service.grpc.pb.h"
#include "asylo/util/status.h"
#include "asylo/util/statusor.h"
#include "include/grpcpp/grpcpp.h"

namespace asylo { namespace test {
class HostCallsClient {
public:
    HostCallsClient(const std::shared_ptr<::grpc::ChannelInterface> &channel): stub_{host_calls::NewStub(channel, ::grpc::StubOptions())}{}
    std::unique_ptr<host_calls::Stub> stub_;
    {% for host_func in host_funcs %}
    unsigned long long  {{host_func}}  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f{%if host_func == "fct_ptr"%},unsigned long long int ptr {% endif %}){
        __requests request;
        __response response;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        {%if host_func == "fct_ptr"%}request.set_ptr(ptr); {% endif %}
        ::grpc::ClientContext client;
        stub_->hc_{{host_func}}(&client, request, &response);
        return response.ret();
    }
    {% endfor %}
};
}
}

extern "C"{
 namespace asylo { namespace test {
HostCallsClient* hcc;
    void hcc_init(const std::shared_ptr<::grpc::ChannelInterface> &channel){
    hcc = new HostCallsClient(channel);
    }
    void hcc_delete(){
    delete hcc;
    }
    {% for host_func in host_funcs %}
    {% if host_func != "fct_ptr" %}
    unsigned long long int {{host_func}}_stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f) {
        return hcc->{{host_func}}(a,b,c,d,e,f);
    }
    {% else %}
    unsigned long long int {{host_func}}_stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d,unsigned long long int e,unsigned long long int f) {
        unsigned long long int ptr;
        asm volatile("mov %%r15, %0" : "=r"(ptr));
        return hcc->{{host_func}}(a,b,c,d,e,f,ptr);
    }
    {% endif %}
    {% endfor %}
}}
}
