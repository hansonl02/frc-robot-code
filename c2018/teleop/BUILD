cc_library(
    name = "main",
    srcs = ["main.cpp"],
    hdrs = ["main.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//muan/teleop:joystick",
        "//muan/wpilib:ds_sender",
        "//muan/queues:queue_manager",
        "//third_party/frc971/control_loops/drivetrain:drivetrain_queues",
        "//c2018/subsystems/climber:climber_subsystem",
        "//c2018/subsystems/score_subsystem:score_subsystem",
    ],
    restricted_to = ["//tools:roborio"],
)
