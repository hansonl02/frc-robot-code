load("/third_party/google/protobuf/protobuf", "cc_proto_library")

cc_library(
    name = "secondaries",
    srcs = ["secondaries.cpp"],
    hdrs = ["secondaries.h"],
    deps = [
        ":secondaries_queues",
        "//c2014/queue_manager",
    ],
)

cc_proto_library(
    name = "secondaries_proto",
    srcs = ["secondaries.proto"],
    default_runtime = "//third_party/google/protobuf",
    protoc = "//third_party/google/protobuf:protoc",
)

cc_library(
    name = "secondaries_queues",
    hdrs = ["queue_types.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":secondaries_proto",
        "//muan/proto:stack_proto",
        "//muan/queues",
    ],
)

cc_test(
    name = "secondaries_test",
    srcs = ["secondaries_test.cpp"],
    deps = [
        ":secondaries",
        "//third_party/google/googletest",
    ],
)
