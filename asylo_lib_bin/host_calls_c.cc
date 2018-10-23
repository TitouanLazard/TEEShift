#include <memory>
#include <string>
#include <type_traits>
#include "asylo_lib_bin/service.grpc.pb.h"
#include "asylo/util/status.h"
#include "asylo/util/statusor.h"
#include "include/grpcpp/grpcpp.h"
int host_enter = 0;
namespace asylo { namespace test {
class HostCallsClient {
public:
    HostCallsClient(const std::shared_ptr<::grpc::ChannelInterface> &channel): stub_{host_calls::NewStub(channel, ::grpc::StubOptions())}{}
    std::unique_ptr<host_calls::Stub> stub_;
    
    unsigned long long  mem_free  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f){
        __requests request;
        __response response;
        host_enter++;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        
        ::grpc::ClientContext client;
        stub_->hc_mem_free(&client, request, &response);
        return response.ret();
    }
    
    unsigned long long  mem_alloc_debug  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f){
        __requests request;
        __response response;
        host_enter++;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        
        ::grpc::ClientContext client;
        stub_->hc_mem_alloc_debug(&client, request, &response);
        return response.ret();
    }
    
    unsigned long long  str_comp  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f){
        __requests request;
        __response response;
        host_enter++;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        
        ::grpc::ClientContext client;
        stub_->hc_str_comp(&client, request, &response);
        return response.ret();
    }
    
    unsigned long long  str_comp_num  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f){
        __requests request;
        __response response;
        host_enter++;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        
        ::grpc::ClientContext client;
        stub_->hc_str_comp_num(&client, request, &response);
        return response.ret();
    }
    
    unsigned long long  str_find_nocase  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f){
        __requests request;
        __response response;
        host_enter++;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        
        ::grpc::ClientContext client;
        stub_->hc_str_find_nocase(&client, request, &response);
        return response.ret();
    }
    
    unsigned long long  str_comp_nocase  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f){
        __requests request;
        __response response;
        host_enter++;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        
        ::grpc::ClientContext client;
        stub_->hc_str_comp_nocase(&client, request, &response);
        return response.ret();
    }
    
    unsigned long long  fct_ptr  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f,unsigned long long int ptr ){
        __requests request;
        __response response;
        host_enter++;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        request.set_ptr(ptr); 
        ::grpc::ClientContext client;
        stub_->hc_fct_ptr(&client, request, &response);
        return response.ret();
    }
    
    unsigned long long  _Z3maxIiET_S0_S0_  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f){
        __requests request;
        __response response;
        host_enter++;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        
        ::grpc::ClientContext client;
        stub_->hc__Z3maxIiET_S0_S0_(&client, request, &response);
        return response.ret();
    }
    
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
    
    
    unsigned long long int mem_free_stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f) {
        return hcc->mem_free(a,b,c,d,e,f);
    }
    
    
    
    unsigned long long int mem_alloc_debug_stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f) {
        return hcc->mem_alloc_debug(a,b,c,d,e,f);
    }
    
    
    
    unsigned long long int str_comp_stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f) {
        return hcc->str_comp(a,b,c,d,e,f);
    }
    
    
    
    unsigned long long int str_comp_num_stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f) {
        return hcc->str_comp_num(a,b,c,d,e,f);
    }
    
    
    
    unsigned long long int str_find_nocase_stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f) {
        return hcc->str_find_nocase(a,b,c,d,e,f);
    }
    
    
    
    unsigned long long int str_comp_nocase_stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f) {
        return hcc->str_comp_nocase(a,b,c,d,e,f);
    }
    
    
    
    unsigned long long int fct_ptr_stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d,unsigned long long int e,unsigned long long int f) {

        unsigned long long int ptr;
        asm volatile("mov %%r15, %0" : "=r"(ptr));
        return hcc->fct_ptr(a,b,c,d,e,f,ptr);
    }
    
    
    
    unsigned long long int _Z3maxIiET_S0_S0__stub  (unsigned long long int a, unsigned long long int b, unsigned long long int c,unsigned long long int d, unsigned long long int e,unsigned long long int f) {
        return hcc->_Z3maxIiET_S0_S0_(a,b,c,d,e,f);
    }
    
    
}}
}