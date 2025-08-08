cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
project(CedarVaultEngine)

# Include custom compiler options
include(cmake/CompilerOptions.cmake)

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
    "$<$<CONFIG:Debug>:DEBUG_MODE>"
    )

#Keeping here for learning
# Set the output directory for runtime files (EXE and DLL)
# set_target_properties(Game PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Game"
# )

# set_target_properties(Engine PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Game"
# )