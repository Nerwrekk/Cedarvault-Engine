project(Game)

# Automatically find all .cpp and .h files
file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(${PROJECT_NAME} ${CPP_FILES} ${HEADER_FILES} )

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# if (WIN32)
#     #keepin it as console for now otherwise we loose logging
#     set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
# elseif(UNIX)
#     # do noting 
# endif()

# includes directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CONAN_INCLUDE_DIRS}
)

# link libraries 
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Engine
)
