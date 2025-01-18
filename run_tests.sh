#!/usr/bin/env bash

cd src/
rm -rf build
mkdir -p build
cd build
cmake ../
cmake --build ./
./server/server_test