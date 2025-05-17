load("@pybind11//:pybind11.bzl", "pybind_extension")

package(default_visibility = ["//visibility:public"])

py_library(
    name = "pybind11",
    srcs = glob(["include/pybind11/**/*.h"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
)
