load("/third_party/google/protobuf/protobuf", "cc_proto_library")

cc_library(
    name = "cam",
    srcs = ["cam.cpp"],
    hdrs = ["cam.h"],
    deps = [
        ":cam_queues",
        "//c2014/queue_manager",
    ],
)

cc_proto_library(
    name = "cam_proto",
    srcs = ["cam.proto"],
    default_runtime = "//third_party/google/protobuf",
    protoc = "//third_party/google/protobuf:protoc",
)

cc_library(
    name = "cam_queues",
    hdrs = ["queue_types.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":cam_proto",
        "//muan/proto:stack_proto",
        "//muan/queues",
    ],
)

cc_test(
    name = "cam_test",
    srcs = ["cam_test.cpp"],
    deps = [
        ":cam",
        "//third_party/google/googletest",
    ],
)
