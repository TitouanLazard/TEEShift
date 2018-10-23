#include <type_traits>
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "asylo_lib_bin/service.grpc.pb.h"
#include "include/grpcpp/grpcpp.h"
int host_enter = 0;


extern "C" unsigned long long int mem_free_stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);



extern "C" unsigned long long int mem_alloc_debug_stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);



extern "C" unsigned long long int str_comp_stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);



extern "C" unsigned long long int str_comp_num_stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);



extern "C" unsigned long long int str_find_nocase_stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);



extern "C" unsigned long long int str_comp_nocase_stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);



extern "C" unsigned long long int fct_ptr_stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int,  unsigned long long int, unsigned long long int);



extern "C" unsigned long long int _Z3maxIiET_S0_S0__stub(unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int, unsigned long long int);



namespace asylo { namespace test {
class HostCallsServer : public host_calls::Service {
    
    private: ::grpc::Status hc_mem_free(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        host_enter++;
        response->set_ret(mem_free_stub(request->arg0(), request->arg1(), request->arg2(),request->arg3(), request->arg4(),request->arg5()));
        return ::grpc::Status::OK;
    }
    
    private: ::grpc::Status hc_mem_alloc_debug(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        host_enter++;
        response->set_ret(mem_alloc_debug_stub(request->arg0(), request->arg1(), request->arg2(),request->arg3(), request->arg4(),request->arg5()));
        return ::grpc::Status::OK;
    }
    
    private: ::grpc::Status hc_str_comp(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        host_enter++;
        response->set_ret(str_comp_stub(request->arg0(), request->arg1(), request->arg2(),request->arg3(), request->arg4(),request->arg5()));
        return ::grpc::Status::OK;
    }
    
    private: ::grpc::Status hc_str_comp_num(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        host_enter++;
        response->set_ret(str_comp_num_stub(request->arg0(), request->arg1(), request->arg2(),request->arg3(), request->arg4(),request->arg5()));
        return ::grpc::Status::OK;
    }
    
    private: ::grpc::Status hc_str_find_nocase(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        host_enter++;
        response->set_ret(str_find_nocase_stub(request->arg0(), request->arg1(), request->arg2(),request->arg3(), request->arg4(),request->arg5()));
        return ::grpc::Status::OK;
    }
    
    private: ::grpc::Status hc_str_comp_nocase(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        host_enter++;
        response->set_ret(str_comp_nocase_stub(request->arg0(), request->arg1(), request->arg2(),request->arg3(), request->arg4(),request->arg5()));
        return ::grpc::Status::OK;
    }
    
    private: ::grpc::Status hc_fct_ptr(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        host_enter++;
        response->set_ret(fct_ptr_stub(request->arg0(), request->arg1(), request->arg2(),request->arg3(), request->arg4(),request->arg5(), request->ptr()));
        return ::grpc::Status::OK;
    }
    
    private: ::grpc::Status hc__Z3maxIiET_S0_S0_(::grpc::ServerContext *context, const __requests *request, __response *response) override {
        host_enter++;
        response->set_ret(_Z3maxIiET_S0_S0__stub(request->arg0(), request->arg1(), request->arg2(),request->arg3(), request->arg4(),request->arg5()));
        return ::grpc::Status::OK;
    }
    


};
}
}