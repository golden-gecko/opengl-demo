project(opengl-demo)

# Add source files
add_executable(
    opengl-demo
    Camera.cpp Camera.hpp
    City.cpp City.hpp
    Common.hpp
    Debug.cpp Debug.hpp
    Dungeon.cpp Dungeon.hpp
    Input.cpp Input.hpp
    Main.cpp
    Math.cpp Math.hpp
    Object.cpp Object.hpp
    Random.cpp Random.hpp
    Render.cpp Render.hpp
    Terrain.cpp Terrain.hpp
    Texture.cpp Texture.hpp
    Tree.cpp Tree.hpp
    Vector.hpp
    Water.cpp Water.hpp
    Window.cpp Window.hpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
    message(ERROR "OpenGL not found")
endif(NOT OPENGL_FOUND)

include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
target_link_libraries(opengl-demo ${OPENGL_LIBRARIES})

# Set properties
set_target_properties(opengl-demo PROPERTIES
    CXX_EXTENSIONS NO
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


