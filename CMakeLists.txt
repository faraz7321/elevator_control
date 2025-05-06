cmake_minimum_required(VERSION 3.14)
project(ElevatorControl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch nlohmann/json
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Fetch cpr (HTTP library)
FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG c9e2c87d30b8ee77beab10e0265c8162d32f5698 # stable release 28.04.2025 8:48pm GMT+2
)
set(CPR_BUILD_TESTS OFF)
set(CPR_BUILD_SSL ON) # optional, for HTTPS
FetchContent_MakeAvailable(cpr)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(elevator_control main.cpp ${SOURCES})

# Link dependencies
target_link_libraries(elevator_control PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
