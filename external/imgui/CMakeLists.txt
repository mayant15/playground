set(IMGUI_INCLUDE_DIRECTORIES include)

set(IMGUI_SOURCES
    src/imgui_demo.cpp
    src/imgui_draw.cpp
    src/imgui_tables.cpp
    src/imgui_widgets.cpp
    src/imgui.cpp

    src/imgui_impl_glfw.cpp
    src/imgui_impl_opengl3.cpp
)

add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE_DIRECTORIES})
target_link_libraries(imgui PUBLIC glfw)