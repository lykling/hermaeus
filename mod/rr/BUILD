load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "rr",
    srcs = ["main.cc"],
    copts = [
    ],
    linkopts = [
    ],
    deps = [
        "//core/dock",
        "//mod/hello/proto:hello_cc_proto",
    ],
)
