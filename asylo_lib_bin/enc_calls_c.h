#include <memory>
#include <string>
#include <type_traits>
#include "asylo_lib_bin/service.grpc.pb.h"
#include "asylo/util/status.h"
#include "asylo/util/statusor.h"
#include "include/grpcpp/grpcpp.h"


namespace asylo { namespace test {
class EncCallsClient {
public:
    EncCallsClient(const std::shared_ptr<::grpc::ChannelInterface> &channel): stub_{enc_calls::NewStub(channel, ::grpc::StubOptions())}{}
    std::unique_ptr<enc_calls::Stub> stub_;
    
    unsigned long long int _ZN14CServerBrowser6FilterEv  (unsigned long long int a,unsigned long long int b, unsigned long long int c, unsigned long long int d,  unsigned long long int e,  unsigned long long int f) {
        __requests request;
        __response response;
        request.set_arg0(a);
        request.set_arg1(b);
        request.set_arg2(c);
        request.set_arg3(d);
        request.set_arg4(e);
        request.set_arg5(f);
        ::grpc::ClientContext client;
        stub_->ec__ZN14CServerBrowser6FilterEv(&client, request, &response);
        return response.ret();
    }
    
    void populate_add(unsigned long long int a){
        __requests request;
        __response response;
        request.set_arg0(a);
        request.set_arg1(a);
        request.set_arg2(a);
        request.set_arg3(a);
        request.set_arg4(a);
        request.set_arg5(a);
        ::grpc::ClientContext client;
        stub_->populate_add(&client, request, &response);
    }

};
}
}