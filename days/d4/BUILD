cc_binary(
    name = "d4",
    srcs = ["main.cpp", "BingoBoard.h"],
    deps = ["bingoboard",
            "//lib/fileinput",
            "//lib/parseseperatevalues"],
    data = [":input.txt",
    ":testinput.txt"],
)

cc_library(
    name = "bingoboard",
    srcs = ["BingoBoard.h"],
    visibility = ["//visibility:public"],
)

