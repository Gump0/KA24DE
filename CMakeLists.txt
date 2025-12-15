cmake_minimum_required(VERSION 3.20)
project(KA24DE)

# Use clang warnings if building with clang/gcc
if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -pedantic)
elseif (MSVC)
    add_compile_options(/W4)
endif()

# Add SDL3 submodule directories
add_subdirectory(vendor/SDL3)
add_subdirectory(vendor/SDL_image)

# Project source
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(KA24DE ${SOURCES})
target_include_directories(KA24DE PRIVATE src)

# Link SDL3
target_link_libraries(KA24DE PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
