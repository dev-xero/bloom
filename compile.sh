#!/bin/bash

echo "compiling main.cc"
clang++ ./src/main.cc -o ./build
echo "done, output file is ./build"
