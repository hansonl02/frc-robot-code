load("/third_party/google/protobuf/protobuf", "cc_proto_library")

cc_library(
    name = "intakes",
    srcs = ["intakes.cpp"],
    hdrs = ["intakes.h"],
    deps = [
        ":intakes_queues",
        "//c2014/queue_manager",
    ],
)

cc_proto_library(
    name = "intakes_proto",
    srcs = ["intakes.proto"],
    default_runtime = "//third_party/google/protobuf",
    protoc = "//third_party/google/protobuf:protoc",
)

cc_library(
    name = "intakes_queues",
    hdrs = ["queue_types.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":intakes_proto",
        "//muan/proto:stack_proto",
        "//muan/queues",
    ],
)

cc_test(
    name = "intakes_test",
    srcs = ["intakes_test.cpp"],
    deps = [
        ":intakes",
        "//third_party/google/googletest",
    ],
)
