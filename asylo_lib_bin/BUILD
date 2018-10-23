#
# Copyright 2018 Asylo authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

licenses(["notice"])  # Apache v2.0

package(
    default_visibility = ["//visibility:public"],
)

load("@com_google_asylo//asylo/bazel:proto.bzl", "asylo_proto_library", "asylo_grpc_proto_library")


load(
    "@com_google_asylo//asylo/bazel:asylo.bzl",
    "enclave_loader",
    "sim_enclave",
)

load("@com_google_protobuf//:protobuf.bzl", "py_proto_library")
# load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")
load("@linux_sgx//:sgx_sdk.bzl", "sgx_enclave", "sgx_enclave_configuration")
# load("//asylo/bazel:proto.bzl", "asylo_grpc_proto_library")

# Example and exercise for using Asylo toolkits.
asylo_proto_library(
    name = "demo_proto",
    srcs = ["demo.proto"],
    deps = ["@com_google_asylo//asylo:enclave_proto"],
)


asylo_grpc_proto_library(
    name = "service_grpc_proto",
    srcs = ["service.proto"],
)


cc_library(
    name = "host_calls_c",
    srcs = ["host_calls_c.cc"],
    copts = ["-fpic","-DPORTABLE_STATUS"],
    deps = [
        ":service_grpc_proto",
        "@com_github_grpc_grpc//:grpc++",
        "@com_google_absl//absl/strings",
        "@com_google_asylo//asylo/util:status",
    ],
)


cc_library(
    name = "enc_calls_c",
    hdrs = ["enc_calls_c.h"],
    copts = ["-fpic","-DPORTABLE_STATUS"],
    deps = [
        ":service_grpc_proto",
        "@com_github_grpc_grpc//:grpc++",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/memory",
        "@com_google_asylo//asylo/util:status",
    ],
)

cc_library(
    name = "lib_hook_p1",
    srcs = ["lib_hook_p1.cc"],
    deps = [
        ":lib_hook_p2",
    ],
    copts = ["-fpic","-O0","-fpermissive"],
    linkopts = ["-fpermissive"],
)

cc_library(
    name = "lib_hook_p2",
    srcs = ["lib_hook_p2.cc"],
    deps = [
        ":enc_calls_c",
        ":service_grpc_proto",
    ],
    copts = ["-fpic","-O0","-fpermissive"],
    linkopts = ["-fpermissive"],
)



cc_library(
    name = "lib_hook",
    deps = [
        ":lib_hook_p1",
        ":lib_hook_p2",
        ":host_calls_s",
    ],
    copts = ["-fpic","-O0","-fpermissive"],
    linkopts = ["-fpermissive"],
)


cc_library(
    name="prog_enc",
    srcs = glob(["enc_temp_*.o"]),
    deps = [
    ":host_calls_c",
    ]

)



cc_library(
    name = "host_calls_s",
    hdrs = ["host_calls_s.h"],
    copts = ["-fpic","-DPORTABLE_STATUS"],
    deps = [
        ":service_grpc_proto",
        ":lib_hook_p2",
        "@com_github_grpc_grpc//:grpc++",
        "@com_google_absl//absl/strings",
        "@com_google_asylo//asylo/util:status",
    ],
)

cc_library(
    name = "enc_calls_s",
    hdrs = ["enc_calls_s.h"],
    copts = ["-fpic","-DPORTABLE_STATUS"],
    deps = [
        ":service_grpc_proto",
        ":prog_enc",
        "@com_github_grpc_grpc//:grpc++",
        "@com_google_absl//absl/strings",
        "@com_google_asylo//asylo/util:status",
    ],
)


sim_enclave(
    name = "enc",
    srcs = ["encl.cc"],
    deps = [
        ":demo_proto_cc",
        ":service_grpc_proto",
        ":host_calls_c",
        ":enc_calls_s",

        "@com_google_absl//absl/strings",
        "@com_google_asylo//asylo:enclave_runtime",
        "@com_google_asylo//asylo/util:status",
        "@com_github_gflags_gflags//:gflags_nothreads",
        "@com_google_asylo//asylo/util:logging",
        "@com_google_asylo//asylo/grpc/util:grpc_server_launcher",
    ],

)



enclave_loader(
    name = "asylo_lib.so",
    linkshared=1,

    srcs = ["enclave_init.cc"],
    enclaves = {"enclave":":enc"},
    loader_args = [""],
    copts=["-fpic"],
    # linkopts=["-L../sgxsdk/lib64","-lsgx_urts_sim", "-lsgx_uae_service_sim"], #To Be Changed if urts_sim lib are not found
    deps = [
    ":demo_proto_cc",
    ":service_grpc_proto",

    ":lib_hook",
    "@com_github_grpc_grpc//:grpc++",
    "@com_github_gflags_gflags//:gflags_nothreads",
    "@com_google_absl//absl/memory",
    "@com_google_asylo//asylo:enclave_client",
    "@com_google_asylo//asylo/util:logging",
    "@com_google_asylo//asylo/grpc/util:grpc_server_launcher",
    ],
)
