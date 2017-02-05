load("/third_party/google/protobuf/protobuf", "cc_proto_library")

cc_library(
    name = "fingers",
    srcs = ["fingers.cpp"],
    hdrs = ["fingers.h"],
    deps = [
        ":fingers_queues",
        "//c2014/queue_manager",
    ],
)

cc_proto_library(
    name = "fingers_proto",
    srcs = ["fingers.proto"],
    default_runtime = "//third_party/google/protobuf",
    protoc = "//third_party/google/protobuf:protoc",
)

cc_library(
    name = "fingers_queues",
    hdrs = ["queue_types.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":fingers_proto",
        "//muan/proto:stack_proto",
        "//muan/queues",
    ],
)

cc_test(
    name = "fingers_test",
    srcs = ["fingers_test.cpp"],
    deps = [
        ":fingers",
        "//third_party/google/googletest",
    ],
)
