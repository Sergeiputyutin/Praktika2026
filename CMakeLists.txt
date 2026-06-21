cmake_minimum_required(VERSION 3.10)
project(Praktika2026 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
    src/*.h
)
add_library(mylib INTERFACE)
target_include_directories(mylib INTERFACE include/)

add_executable(Praktika2026 ${APP_SOURCES})

target_link_libraries(Praktika2026 PRIVATE mylib)