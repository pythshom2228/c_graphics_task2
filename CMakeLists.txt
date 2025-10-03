cmake_minimum_required(VERSION 3.20)

set(PROJ_NAME c_graphics_task2)
set(LIB_NAME edu_sort_and_search)

project(${PROJ_NAME} LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_C_STANDARD 11)

set(CRITERION_DIR "${CMAKE_SOURCE_DIR}/external/criterion-2.4.2")

add_library(
        ${LIB_NAME}
        STATIC
        src/edu_sort.c
        src/edu_search.c
)

target_include_directories(${LIB_NAME} PUBLIC include)
target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,leak,undefined")

enable_testing()
add_subdirectory(test)
