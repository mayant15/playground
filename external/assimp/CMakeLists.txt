
message(STATUS "Fetching Assimp...")

FetchContent_Declare(
    assimp 
    GIT_REPOSITORY "https://github.com/assimp/assimp"
    GIT_TAG 80b0b897edfc8d97a3071033b95dcd6b799e403b
)

set(ASSIMP_BUILD_TESTS OFF)

FetchContent_MakeAvailable(assimp)
