cmake_minimum_required(VERSION 3.14)
project(p_project)

set(CMAKE_C_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/extlib/cereal-1.3.2/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/extlib/imgui-1.89.2)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/extlib/imgui-1.89.2/backends)

INCLUDE_DIRECTORIES(/usr/include/SDL2)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(OpenGL REQUIRED)

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

        "${ACTUAL_SOURCE_DIR}/examples/*.h"
        "${ACTUAL_SOURCE_DIR}/examples/*.hpp"
        "${ACTUAL_SOURCE_DIR}/examples/*.cpp"
        "${ACTUAL_SOURCE_DIR}/examples/*.c"

        "${PROJECT_SOURCE_DIR}/extlib/imgui-1.89.2/backends/imgui_impl_sdl.cpp"
        "${PROJECT_SOURCE_DIR}/extlib/imgui-1.89.2/backends/imgui_impl_opengl3.cpp"
)

add_executable(p_project p_project/main.cpp ${all_SRCS})

target_compile_features(p_project PRIVATE cxx_std_17)
target_link_libraries(p_project -lstdc++fs SDL2 OpenGL ${CMAKE_DL_LIBS})

if (UNIX)
    # target_link_libraries(p_project )
endif()

if (WIN32 AND BUILD_SHARED_LIBS)
    #add_custom_command(TARGET p_project POST_BUILD
            #COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:p_project> $<TARGET_FILE_DIR:p_project> COMMAND_EXPAND_LISTS)

    #install(TARGETS p_project)
endif()



