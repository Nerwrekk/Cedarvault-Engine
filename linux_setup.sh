# !/bin/bash

target="Targets/$1"

conan install . --output-folder=$target --build missing -s build_type=$1 -c tools.system.package_manager:sudo=True -c tools.system.package_manager:mode=install 

# possible build types: ['Debug', 'Release', 'RelWithDebInfo', 'MinSizeRel']
cmake -S . -B $target -DCMAKE_BUILD_TYPE=$1 -DCMAKE_TOOLCHAIN_FILE="$target/build/$1/generators/conan_toolchain.cmake"

cmake --build $target --config $1