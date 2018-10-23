#include <type_traits>
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "asylo_lib_bin/service.grpc.pb.h"
#include "include/grpcpp/grpcpp.h"
int host_enter = 0;
{% for host_func in host_funcs %}
{% if host_func == "fct_ptr" %}
extern "C" unsigned long long int {{host_func}}_stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int,  unsigned long long int, unsigned long long int);
{% else %}
extern "C" unsigned long long int {{host_func}}_stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);
{% endif%}
{% endfor %}

namespace asylo { namespace test {
class HostCallsServer : public host_calls::Service {
    {% for host_func in host_funcs %}
    private: ::grpc::Status hc_{{host_func}}(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        host_enter++;
        response->set_ret({{host_func}}_stub(request->arg0(), request->arg1(), request->arg2(),request->arg3(), request->arg4(),request->arg5(){% if host_func == "fct_ptr" %}, request->ptr(){% endif%}));
        return ::grpc::Status::OK;
    }
    {% endfor %}


};
}
}
