message(STATUS "Fetching spdlog...")

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog"
    GIT_TAG eb3220622e73a4889eee355ffa37972b3cac3df5
)

FetchContent_MakeAvailable(spdlog)
