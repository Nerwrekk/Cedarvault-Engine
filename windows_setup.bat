@echo off 

rem output directory 
set target="Targets/%1" 

rem install conan dependencies 
rem possible build types: ['Debug', 'Release', 'RelWithDebInfo', 'MinSizeRel']
conan install . --output-folder=%target% --build=missing -s build_type=%1 -c tools.system.package_manager:mode=install

rem generate cmake build files -DCMAKE_TOOLCHAIN_FILE="conanbuildinfo.cmake" 
cmake -S . -B %target% -DCMAKE_BUILD_TYPE=%1 -DCMAKE_TOOLCHAIN_FILE="%target%/build/generators/conan_toolchain.cmake"

rem compile cmake build files 
cmake --build %target% --config %1

