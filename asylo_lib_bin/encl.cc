
#include <iostream>
#include <string>

#include "asylo_lib_bin/demo.pb.h"
#include "asylo/trusted_application.h"
// #include "host_calls_c.h"
#include "enc_calls_s.h"
#include "asylo/util/statusor.h"
#include "asylo/grpc/util/grpc_server_launcher.h"
#include "absl/memory/memory.h"


extern "C" void hcc_init(const std::shared_ptr<::grpc::ChannelInterface> &channel);
extern "C" void hcc_delete();
extern int enclave_enter;
extern int host_enter;


namespace asylo {

class EnclaveDemo : public TrustedApplication {
 public:
  EnclaveDemo() = default;
  bool launched = false;
  GrpcServerLauncher *launcher;
  std::shared_ptr<::grpc::Channel> channel;
  Status Run(const EnclaveInput &input, EnclaveOutput *output) {
    if (!launched) {
        std::cout << "ENCLAVE LAUNCHING PROCESS" << std::endl;
        channel = ::grpc::CreateChannel("localhost:5_044", ::grpc::InsecureChannelCredentials());
        hcc_init(channel);
        launcher = new GrpcServerLauncher("Launcher");
        std::cout << (launcher->GetState() ==  GrpcServerLauncher::State::LAUNCHED)<< std::endl;
        std::string add =  "localhost:4045";
        launcher->AddListeningPort(add,::grpc::InsecureServerCredentials());
        launcher->RegisterService(absl::make_unique<test::EncCallsServer>());
        launcher->Start();
        std::cout << "ENCI == CC : " << (launcher->GetState() == GrpcServerLauncher::State::LAUNCHED) << std::endl;
        launched = true;
    }else{
        launcher->Shutdown();
        std::cout << "ENCD == CC : " << (launcher->GetState() == GrpcServerLauncher::State::TERMINATED) << std::endl;
        std::cout << "Total enclave enter : " << enclave_enter << std::endl;
        std::cout << "Total host enter : " << host_enter << std::endl;
        hcc_delete();
    }

    return Status::OkStatus();
  }

};

TrustedApplication *BuildTrustedApplication() { return new EnclaveDemo; }

}  // namespace asylo
