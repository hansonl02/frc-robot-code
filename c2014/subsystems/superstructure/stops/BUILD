load("/third_party/google/protobuf/protobuf", "cc_proto_library")

cc_library(
    name = "stops",
    srcs = ["stops.cpp"],
    hdrs = ["stops.h"],
    deps = [
        ":stops_queues",
        "//c2014/queue_manager",
    ],
)

cc_proto_library(
    name = "stops_proto",
    srcs = ["stops.proto"],
    default_runtime = "//third_party/google/protobuf",
    protoc = "//third_party/google/protobuf:protoc",
)

cc_library(
    name = "stops_queues",
    hdrs = ["queue_types.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":stops_proto",
        "//muan/proto:stack_proto",
        "//muan/queues",
    ],
)

cc_test(
    name = "stops_test",
    srcs = ["stops_test.cpp"],
    deps = [
        ":stops",
        "//third_party/google/googletest",
    ],
)
