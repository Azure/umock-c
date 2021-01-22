#!/bin/bash
# Copyright (c) Microsoft. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

set -e

build_root=$(cd "$1" && pwd)
cd $build_root

build_folder=$build_root"/cmake_linux_iwyu"

# Set the default cores
CORES=$(grep -c ^processor /proc/cpuinfo 2>/dev/null || sysctl -n hw.ncpu)

rm -r -f $build_folder
mkdir -p $build_folder
pushd $build_folder
CC="clang" CXX="clang++" cmake $build_root -GNinja -DCMAKE_C_INCLUDE_WHAT_YOU_USE:UNINITIALIZED="include-what-you-use;-Xiwyu;--mapping_file=$build_root/deps/c-build-tools/iwyu/rules.imp;" -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE:UNINITIALIZED="include-what-you-use;-Xiwyu;--mapping_file=$build_root/deps/c-build-tools/iwyu/rules.imp;" -Drun_unittests:bool=ON -Drun_int_tests:bool=ON
cmake --build . > >(tee $build_folder"/build.log") 2> >(tee $build_folder"/builderror.log" >&2)

if grep 'Warning:' $build_folder"/builderror.log"; then
    echo "Failing build due to iwyu warnings"
    exit -1
fi

if grep 'Warning:' $build_folder"/build.log"; then
    echo "Failing build due to iwyu warnings"
    exit -1
fi

popd