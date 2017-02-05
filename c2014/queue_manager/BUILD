cc_library(
    name = "queue_manager",
    srcs = ["queue_manager.cpp"],
    hdrs = ["queue_manager.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//c2014/subsystems/superstructure/stops:stops_queues",
        "//c2014/subsystems/superstructure/secondaries:secondaries_queues",
        "//c2014/subsystems/superstructure/intakes:intakes_queues",
        "//c2014/subsystems/superstructure/fingers:fingers_queues",
        "//c2014/subsystems/superstructure/cam:cam_queues",
        "//c2014/wpilib:wpilib_queues",
        "//muan/proto:stack_proto",
        "//muan/queues",
        "//muan/wpilib:wpilib_queues",
        "//third_party/frc971/control_loops/drivetrain:drivetrain_lib",
    ],
)

cc_test(
    name = "queue_manager_test",
    srcs = ["test_queue_manager.cpp"],
    deps = [
        ":queue_manager",
        "//third_party/google/googletest",
    ],
)
