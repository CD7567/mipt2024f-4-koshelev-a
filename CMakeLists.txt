cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(mipt2024s-3-koshelev-a)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
## profiles settings ##########################################################
###############################################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
    set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer -fsanitize=address")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DNDEBUG)
endif ()

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        RECT_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

file(
        GLOB_RECURSE
        RECT_LIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.cpp
)

set(
        MAIN_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        rect-lib
        ${RECT_LIB_HEADERS}
        ${RECT_LIB_SOURCES}
)

target_include_directories(
        rect-lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(
        main
        ${MAIN_SOURCES}
)


configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/config.toml
        ${CMAKE_CURRENT_BINARY_DIR}
        COPYONLY
)

###############################################################################
## dependencies ###############################################################
###############################################################################

find_package(
        OpenCV REQUIRED
)

find_package(
        spdlog REQUIRED
)

find_package(
        nlohmann_json REQUIRED
)

target_link_libraries(
        rect-lib
        PUBLIC
        ${OpenCV_LIBS}
        spdlog::spdlog
        nlohmann_json::nlohmann_json
)

target_link_libraries(
        main
        PUBLIC
        ${OpenCV_LIBS}
        spdlog::spdlog
        nlohmann_json::nlohmann_json
        rect-lib
)
