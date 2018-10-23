#include <type_traits>
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "asylo_lib_bin/service.grpc.pb.h"
#include "include/grpcpp/grpcpp.h"
int enclave_enter = 0;
extern "C" unsigned long long int base_add;
unsigned long long int base_add = 0;

extern "C" unsigned long long int _ZN14CServerBrowser6FilterEv(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);

extern "C" unsigned long long int get_base_add(){
    return base_add;
}
namespace asylo { namespace test {
class EncCallsServer : public enc_calls::Service {
    
    private: ::grpc::Status ec__ZN14CServerBrowser6FilterEv(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        enclave_enter++;
        response->set_ret(_ZN14CServerBrowser6FilterEv(request->arg0(), request->arg1(), request->arg2(),request->arg3(),request->arg4(),request->arg5()));
        return ::grpc::Status::OK;
    }
    
    private: ::grpc::Status populate_add(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        base_add = request->arg0();
        response->set_ret(0);
        return ::grpc::Status::OK;
    }


};
}
}