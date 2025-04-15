cc_test(
    name = "kivsee-render-test",
    srcs = glob([
        "*.pb.cc",
        "*.cpp",
        "*.pb.h",
    ]),
    copts = [
        "-Iinclude",
        "/std:c++20",
    ],
    deps = [
        "@googletest//:gtest_main",
        "@protobuf//:protobuf",
        "//:kivsee-render",
    ],
    size="small",
)