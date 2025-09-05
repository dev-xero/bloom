#!/bin/bash

echo -e "CMAKE generating build systems\n"
cmake -B build .

echo -e "\nBuilding source files\n"
cmake --build build

echo -e "\nDone"

