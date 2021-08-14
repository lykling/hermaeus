load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_proto_library")

package(default_visibility = ["//visibility:public"])

cc_proto_library(
    name = "hello_cc_proto",
    deps = [
        ":hello_proto",
    ],
)

proto_library(
    name = "hello_proto",
    srcs = ["hello.proto"],
)
