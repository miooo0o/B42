cmake_minimum_required(VERSION 3.10)
project(so_long)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -g")

include_directories(include)
include_directories(./lib/MLX42/include)


file(GLOB SOURCES "src/*.c")
file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(so_long ${SOURCES})

add_subdirectory(lib/MLX42)

target_link_libraries(so_long MLX42)
