cmake_minimum_required(VERSION 3.10)
project(MissionLoveOps)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.c")

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find Lua
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# Add executable
add_executable(MissionLoveOps ${SOURCES})

# Link libraries
target_link_libraries(MissionLoveOps ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${LUA_LIBRARIES})
