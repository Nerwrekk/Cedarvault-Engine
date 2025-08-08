project(Game)

# Automatically find all .cpp and .h files
file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(${PROJECT_NAME} ${CPP_FILES} ${HEADER_FILES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
if(WIN32)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        file(COPY C:/dev/CedarVault-Engine/Game/TankGame/bin/Debug/net8.0/TankGame.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
        file(COPY C:/dev/CedarVault-Engine/Game/TankGame/bin/Debug/net8.0/TankGame.pdb DESTINATION ${CMAKE_BINARY_DIR}/bin)
    else()
        file(COPY C:/dev/CedarVault-Engine/Game/TankGame/bin/Release/net8.0/TankGame.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
    endif()
else()
    file(COPY include/MeanScript/MeanManaged/MeanScripting/publish/linux/MeanScripting.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif()

if (WIN32)
    #keepin it as console for now otherwise we loose logging
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
elseif(UNIX)
    # do noting 
endif()

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

setup_compile_options(${PROJECT_NAME})