cmake_minimum_required(VERSION 4.3.1)

# Project
project(opengl-demo)

# Sources
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Target
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS NO
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# GLU (OpenGL Utility Library)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GLU)
