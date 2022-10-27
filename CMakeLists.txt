cmake_minimum_required(VERSION 3.14)
project(p_project)

set(CMAKE_C_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# raylib is there
INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

find_package(SFML COMPONENTS graphics window system REQUIRED)

set(ACTUAL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/p_project)

INCLUDE_DIRECTORIES(
        ${ACTUAL_SOURCE_DIR}/common/include/
        ${ACTUAL_SOURCE_DIR}/common/src/
        ${ACTUAL_SOURCE_DIR}/game/include/
        ${ACTUAL_SOURCE_DIR}/game/src/
        ${ACTUAL_SOURCE_DIR}/map_maker/include/
        ${ACTUAL_SOURCE_DIR}/map_maker/src/
        ${ACTUAL_SOURCE_DIR}/tools/include/
        #${PROJECT_SOURCE_DIR}/src/tools/
)

file(GLOB all_SRCS
        "${ACTUAL_SOURCE_DIR}/common/include/*.h"
        "${ACTUAL_SOURCE_DIR}/common/include/*.hpp"
        "${ACTUAL_SOURCE_DIR}/common/src/*.cpp"
        "${ACTUAL_SOURCE_DIR}/common/src/*.c"

        "${ACTUAL_SOURCE_DIR}/game/include/*.h"
        "${ACTUAL_SOURCE_DIR}/game/include/*.hpp"
        "${ACTUAL_SOURCE_DIR}/game/src/*.cpp"
        "${ACTUAL_SOURCE_DIR}/game/src/*.c"

        "${ACTUAL_SOURCE_DIR}/map_maker/include/*.h"
        "${ACTUAL_SOURCE_DIR}/map_maker/include/*.hpp"
        "${ACTUAL_SOURCE_DIR}/map_maker/src/*.cpp"
        "${ACTUAL_SOURCE_DIR}/map_maker/src/*.c"

        "${ACTUAL_SOURCE_DIR}/tools/include/*.h"
        "${ACTUAL_SOURCE_DIR}/tools/include/*.hpp"
        "${ACTUAL_SOURCE_DIR}/tools/src/*.cpp"
        "${ACTUAL_SOURCE_DIR}/tools/src/*.c"
)

add_executable(p_project p_project/main.cpp ${all_SRCS})

target_compile_features(p_project PUBLIC cxx_std_17)
target_compile_definitions(p_project PRIVATE SFML_STATIC)
target_link_libraries(p_project libraylib.so)
target_link_libraries(p_project sfml-window sfml-graphics  sfml-system)