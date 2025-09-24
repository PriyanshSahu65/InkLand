cmake_minimum_required(VERSION 3.24...3.30)
project(InkLand LANGUAGES CXX)

include(FetchContent)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Raylib setup
set(RAYLIB_VERSION 5.0)
FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Source files
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include headers
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Link Raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}"
)

# Copy entire assets folder (including subfolders) to runtime resources/
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
)
