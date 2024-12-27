cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
project(CedarVaultEngine)

# Set the C++ standard
set(CMAKE_CONFIGURATION_TYPES Debug Release) 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE) 
set(CMAKE_CXX_EXTENSIONS ON) 

# build output directories 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/bin) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/bin) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/lib) 
set(CMAKE_PDB_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/lib) 
set(EXECUTABLE_OUTPUT_PATH $<0:>${CMAKE_BINARY_DIR}/bin)

# project subdirectories 
add_subdirectory(Engine) 
add_subdirectory(Game)

target_compile_definitions(Engine PUBLIC
    #this is called a generator expression and here we check if the current config is currently Debug
    #and if it is it applies the define.
    "$<$<CONFIG:Debug>:CEDAR_ENABLE_LOG>"
    )
