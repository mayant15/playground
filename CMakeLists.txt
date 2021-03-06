cmake_minimum_required(VERSION 3.22)
project(playground)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Export a compilation database for YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setup dependencies
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/spdlog)
add_subdirectory(external/imgui)
add_subdirectory(external/assimp)

add_subdirectory(photon)

set(SOURCES
  src/main.cpp
  src/Window.cpp
  src/VertexArrayInfo.cpp
  src/utility/ui.cpp
)

add_executable(playground ${SOURCES})
target_include_directories(playground PUBLIC src)
target_link_libraries(playground PUBLIC glm glfw glad spdlog imgui photon)
