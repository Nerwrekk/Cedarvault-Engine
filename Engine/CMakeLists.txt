project(Engine VERSION 0.0.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Automatically find all .cpp and .h files
file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(${PROJECT_NAME} SHARED ${CPP_FILES} ${HEADER_FILES})

#export engine sympols
# target_compile_definitions(${PROJECT_NAME} PUBLIC DEFINITION) 

#find third-party packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(sol2 REQUIRED)
find_package(glm REQUIRED)

# includes directories
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CONAN_INCLUDE_DIRS}
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
    ${CONAN_LIBS}
    SDL2::SDL2main
    SDL2_image::SDL2_image
    sol2::sol2
    glm::glm
)
