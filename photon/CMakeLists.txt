set(PHOTON_INCLUDE_DIR include)

set(PHOTON_SOURCES
    src/photon.cpp
    src/ShaderCache.cpp
)

add_library(photon ${PHOTON_SOURCES})
target_include_directories(photon PUBLIC ${PHOTON_INCLUDE_DIR})
target_link_libraries(photon PUBLIC glad glm)

