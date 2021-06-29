
cc_test(
    name = "kivsee-render-test",
    srcs = glob([
        "*.pb.cc",
        "*.cpp",
        "*.pb.h",
    ]),
    copts = ["-Iexternal/gtest/include", "-Iinclude"],
    deps = [
        "@gtest//:gtest_main",
        "@com_google_protobuf//:protobuf",
        "//:kivsee-render",
    ],
)