load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "dock",
    srcs = ["dock.cc"],
    hdrs = ["dock.h"],
    linkopts = [
        "-lstdc++",
        "-lfastcdr",
        "-lfastrtps",
    ],
    deps = [
        ":carrier_message_pub_sub_types",
        ":participant",
        ":reader",
        ":reader_base",
        ":writer",
        ":writer_base",
    ],
)

cc_library(
    name = "reader",
    srcs = ["reader.cc"],
    hdrs = ["reader.h"],
    linkopts = [
        "-lfastrtps",
    ],
    deps = [
        ":carrier_message",
        ":participant",
        ":reader_base",
    ],
)

cc_library(
    name = "reader_base",
    srcs = ["reader_base.cc"],
    hdrs = ["reader_base.h"],
    deps = [
    ],
)

cc_library(
    name = "writer",
    srcs = ["writer.cc"],
    hdrs = ["writer.h"],
    linkopts = [
        "-lfastrtps",
    ],
    deps = [
        ":carrier_message",
        ":participant",
        ":writer_base",
    ],
)

cc_library(
    name = "writer_base",
    srcs = ["writer_base.cc"],
    hdrs = ["writer_base.h"],
    deps = [
    ],
)

cc_library(
    name = "carrier_message",
    srcs = ["carrier_message.cc"],
    hdrs = ["carrier_message.h"],
    linkopts = [
        "-lfastcdr",
    ],
)

cc_library(
    name = "carrier_message_pub_sub_types",
    srcs = ["carrier_message_pub_sub_types.cc"],
    hdrs = ["carrier_message_pub_sub_types.h"],
    linkopts = [
        "-lfastcdr",
    ],
    deps = [
        ":carrier_message",
    ],
)

cc_library(
    name = "participant",
    srcs = ["participant.cc"],
    hdrs = ["participant.h"],
    linkopts = [
        "-lfastrtps",
    ],
    deps = [
        ":carrier_message_pub_sub_types",
    ],
)
