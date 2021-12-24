cmake_minimum_required(VERSION 3.22)
project(playground)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Setup dependencies
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/spdlog)

set(SOURCES
  src/main.cpp
)

add_executable(playground ${SOURCES})
target_link_libraries(playground glm glfw glad spdlog)
