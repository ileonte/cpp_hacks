#!/bin/bash

CXX=${CXX:-g++}
STRIP=${STRIP:-strip}
STATIC=${STATIC:--static}

echo "Building small executable"
${CXX} -std=c++17 test.cpp -fno-exceptions -fno-rtti -O3 -g ${STATIC} -o test-small
${STRIP} --strip-unneeded -R .comment test-small
echo "Building large executable"
${CXX} -std=c++17 test.cpp -fno-exceptions -fno-rtti -DPULL_IN_STL -O3 -g ${STATIC} -o test-large
${STRIP} --strip-unneeded -R .comment test-large
