cmake_minimum_required(VERSION 3.14)
project(p_project)

set(CMAKE_C_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# raylib is there
INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

set(ACTUAL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/p_project)

INCLUDE_DIRECTORIES(
        ${ACTUAL_SOURCE_DIR}/game/include/
        ${ACTUAL_SOURCE_DIR}/game/src/
        ${ACTUAL_SOURCE_DIR}/map_maker/include/
        ${ACTUAL_SOURCE_DIR}/map_maker/src/
        ${ACTUAL_SOURCE_DIR}/tools/include/
        #${PROJECT_SOURCE_DIR}/src/tools/
)

file(GLOB all_SRCS
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
        #"${ACTUAL_SOURCE_DIR}tools/src/*.cpp"
        #"${ACTUAL_SOURCE_DIR}tools/src/*.c"
)

add_executable(p_project p_project/main.cpp ${all_SRCS} p_project/game/src/map.cpp p_project/game/src/world.cpp p_project/map_maker/include/constants.h p_project/map_maker/include/params.h p_project/tools/src/tools.cpp)

TARGET_LINK_LIBRARIES(p_project libraylib.so)