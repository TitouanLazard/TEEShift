#include <type_traits>
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "asylo_lib_bin/service.grpc.pb.h"
#include "include/grpcpp/grpcpp.h"
int enclave_enter = 0;
{% for enc_func in enc_funcs %}
extern "C" unsigned long long int {{enc_func}}(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);
{% endfor %}

namespace asylo { namespace test {
class EncCallsServer : public enc_calls::Service {
    {% for enc_func in enc_funcs %}
    private: ::grpc::Status ec_{{enc_func}}(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        enclave_enter++;
        response->set_ret({{enc_func}}(request->arg0(), request->arg1(), request->arg2(),request->arg3(),request->arg4(),request->arg5()));
        return ::grpc::Status::OK;
    }
    {% endfor %}


};
}
}
