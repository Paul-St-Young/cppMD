#!/bin/bash

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make

./cppMD 0.728
