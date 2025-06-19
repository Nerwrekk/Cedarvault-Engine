project(Engine VERSION 0.0.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Include custom compiler options
include(../cmake/MeanScriptDotnetSetup.cmake)

# Automatically find all .cpp and .h files
file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(${PROJECT_NAME} SHARED ${CPP_FILES} ${HEADER_FILES})
# Apply compiler options to targets
setup_compile_options(${PROJECT_NAME})

#export engine sympols
#target_compile_definitions Scopes:
# PRIVATE: The definition will only apply to the target being built. It is not propagated to other targets that link against this one.
# PUBLIC: The definition will apply to the target being built and to any targets that link against this target. This means if another target links against your shared library, it will inherit these preprocessor definitions.
# Use PRIVATE when the definition is only relevant for the target itself and not for targets that link against it.
# Use PUBLIC when you need the definition to be shared with other targets that link against your target. This is often the case with headers that require specific macros to work properly when used by other code.
target_compile_definitions(${PROJECT_NAME} PRIVATE CEDAR_EXPORT) 

#copy nethost.dll
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${NETHOST_DLL}"
            $<TARGET_FILE_DIR:Engine>
)

file(COPY include/MeanScript/meanscript.runtimeconfig.json DESTINATION ${CMAKE_BINARY_DIR}/bin)
if(WIN32)
    file(COPY include/MeanScript/MeanManaged/GameScripting/publish/win/MeanScripting.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
else()
    file(COPY include/MeanScript/MeanManaged/GameScripting/publish/linux/MeanScripting.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif()
#find third-party packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(sol2 REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

# Find nethost.lib (used to locate .NET runtime)
if(WIN32)
    find_library(NETHOST_LIB 
        NAMES nethost.lib
        PATHS ${NETHOST_NATIVE_PATH}
    )
else()
    find_library(NETHOST_LIB 
        NAMES libnethost.a  
        PATHS ${NETHOST_NATIVE_PATH}
    )
endif()

# Ensure the library was found
if(NOT NETHOST_LIB)
    message(FATAL_ERROR "nethost.lib not found! Install .NET Hosting Bundle.")
endif()

# includes directories
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CONAN_INCLUDE_DIRS}
    ${NETHOST_NATIVE_PATH}
)

# add_custom_command(TARGET Cedar
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/assets/simple-shader.vs ${PROJECT_BINARY_DIR}
#     COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/assets/simple-shader.fs ${PROJECT_BINARY_DIR}
# )

# link directories 
target_link_directories(${PROJECT_NAME} PUBLIC 
    ${CONAN_LIB_DIRS}
)

# link libraries 
target_link_libraries(${PROJECT_NAME} PUBLIC 
    ${NETHOST_LIB}
    ${CONAN_LIBS}
    spdlog::spdlog
    SDL2::SDL2main
    SDL2_image::SDL2_image
    sol2::sol2
    glm::glm
)
