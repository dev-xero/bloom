#!/bin/bash

echo -e "CMAKE generating build systems\n"
cmake -B build .

echo -e "\nBuilding source files\n"
if ! cmake --build build ; then
    echo "Build failed"
    exit
fi

echo -e "\nDone"

