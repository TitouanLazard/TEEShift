

#include "asylo_lib_bin/demo.pb.h"
#include "asylo/client.h"
#include "gflags/gflags.h"
#include "asylo/util/logging.h"


#include "asylo/client.h"
#include "gflags/gflags.h"
#include "host_calls_s.h"
#include "asylo/grpc/util/grpc_server_launcher.h"
#include "include/grpcpp/grpcpp.h"


extern "C" void ecc_init(const std::shared_ptr<::grpc::ChannelInterface> &channel);
extern "C" void ecc_delete();

asylo::GrpcServerLauncher *launcher;
char launched;

extern "C" int init_enclave();
int init_enclave(){

        launcher = new asylo::GrpcServerLauncher("my launcher");
        std::string add =  "localhost:5044";
        launcher->AddListeningPort(add,::grpc::InsecureServerCredentials());
        launcher->RegisterService(absl::make_unique<asylo::test::HostCallsServer>());
        launcher->Start();
        std::cout << "CC : " << (launcher->GetState() == asylo::GrpcServerLauncher::State::LAUNCHED) << std::endl;

        asylo::EnclaveManager::Configure(asylo::EnclaveManagerOptions());
        auto manager_result = asylo::EnclaveManager::Instance();
        LOG_IF(QFATAL, !manager_result.ok()) << "Could not obtain EnclaveManager";

        asylo::EnclaveManager *manager = manager_result.ValueOrDie();
        asylo::SimLoader loader("/tmp/enc", /*debug=*/true);
        asylo::Status status = manager->LoadEnclave("my_enclaved_functions", loader);
        LOG_IF(QFATAL, !status.ok()) << "LoadEnclave failed with: " << status;

        // Part 2: Secure execution

        asylo::EnclaveClient *client = manager->GetClient("my_enclaved_functions");
        asylo::EnclaveInput input;
        asylo::EnclaveOutput output;
        status = client->EnterAndRun(input, &output);

        LOG_IF(QFATAL, !status.ok()) << "EnterAndRun failed with: " << status;


        std::shared_ptr<::grpc::Channel> channel = ::grpc::CreateChannel("localhost:4045", ::grpc::InsecureChannelCredentials());
        ecc_init(channel);
        launched = 1;

        return 0;
}

int shutdown_enclave() __attribute__((destructor()));
int shutdown_enclave(){
    if(launched){
        auto manager_result = asylo::EnclaveManager::Instance();
        LOG_IF(QFATAL, !manager_result.ok()) << "Could not obtain EnclaveManager";
        std::cout  << "[+] Destroy the Enclave"<< std::endl;
        asylo::EnclaveManager *manager = manager_result.ValueOrDie();
        asylo::EnclaveClient *client = manager->GetClient("my_enclaved_functions");
        asylo::EnclaveInput input;
        asylo::EnclaveOutput output;

        ecc_delete();
        launcher->Shutdown();
        client->EnterAndRun(input, &output);
        std::cout << "Every thing went well!" << std::endl;
        asylo::EnclaveFinal empty_final_input;
        manager->DestroyEnclave(client, empty_final_input);
        // LOG_IF(QFATAL, !status.ok()) << "DestroyEnclave failed with: " << status;
    }
    return 0;
}
//
// extern "C" int get_launch_token();
// int get_launch_token(){
//  return 0;
// }
