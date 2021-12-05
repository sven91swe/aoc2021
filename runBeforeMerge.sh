#!/bin/bash
bazel build --copt="-Werror" //...

clang-format -i $(find -iname *.cpp -o -iname *.h)