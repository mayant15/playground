cmake_minimum_required(VERSION 3.22)
project(playground)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Setup dependencies
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/spdlog)
add_subdirectory(external/imgui)

set(SOURCES
  src/main.cpp
  src/Window.cpp
  src/utility/ui.cpp
)

add_executable(playground ${SOURCES})
target_include_directories(playground PUBLIC src)
target_link_libraries(playground PUBLIC glm glfw glad spdlog imgui)
