project(Editor)

# Automatically find all .cpp and .h files
file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(${PROJECT_NAME} ${CPP_FILES} ${HEADER_FILES})

# file(COPY assets DESTINATION ${CMAKE_SOURCE_DIR}/bin)
if(WIN32)
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/TankGame/bin/Debug/net8.0/TankGame.dll DESTINATION ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin)
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/TankGame/bin/Debug/net8.0/TankGame.pdb DESTINATION ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin)
else()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/TankGame/bin/Debug/net8.0/TankGame.dll DESTINATION ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin)
    # file(COPY include/MeanScript/MeanManaged/MeanScripting/publish/linux/MeanScripting.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif()

if (WIN32)
    #keepin it as console for now otherwise we loose logging
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
elseif(UNIX)
    # do noting 
endif()

set_target_properties(Editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin"
)

# link libraries 
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Engine
)

# includes directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CONAN_INCLUDE_DIRS}
)

if (WIN32)
add_custom_command(
    TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/bin/meanscript.runtimeconfig.json"
        "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin/"
     COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/bin/MeanScripting.dll"
        "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin/"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/bin/nethost.dll"
        "${CMAKE_SOURCE_DIR}/Editor/bin/"
)
else()
add_custom_command(
    TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/bin/meanscript.runtimeconfig.json"
        "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin/meanscript.runtimeconfig.json"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/bin/MeanScripting.dll"
        "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin/"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/bin/nethost.so"
        "${CMAKE_SOURCE_DIR}/Editor/bin/"
)
endif()


setup_compile_options(${PROJECT_NAME})