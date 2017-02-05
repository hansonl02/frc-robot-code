load("//muan/deploy:deploy.bzl", "muan_deploy")

cc_binary(
    name = "frc1678",
    srcs = ["main.cpp"],
    deps = [
        "//c2014/subsystems:subsystem_runner",
        "//c2014/wpilib_update:main",
        "//third_party/wpilibsuite:wpilib",
    ],
    data = [
        "//c2014/lemonscript/auto:auto_modes",
    ]
)

muan_deploy(
    name = "deploy",
    main = ":frc1678",
)
