cmake_minimum_required(VERSION 3.16)
project(crow_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
# enable_testing()

# GLOB all source files in respective directories
file(GLOB ROUTES_SRC "src/routes/*.cpp")
file(GLOB UTILS_SRC "src/utils/*.cpp")
file(GLOB TESTS_SRC "tests/*.cpp")
file(GLOB MAIN_SRC "src/main.cpp")

# Shared library for reusable components (e.g., routes and utilities)
add_library(crow_lib ${ROUTES_SRC} ${UTILS_SRC})

# Include directories for the shared library
target_include_directories(crow_lib PUBLIC include third_party/crow)

target_link_libraries(crow_lib PRIVATE sqlite3)

# Main executable
add_executable(crow_project ${MAIN_SRC})

# Link the shared library to the main executable
target_link_libraries(crow_project PRIVATE crow_lib)

# Test executable (uncomment if needed)
# add_executable(tests ${TESTS_SRC})
# target_link_libraries(tests PRIVATE crow_lib)
# add_test(NAME TestRoutes COMMAND tests)
