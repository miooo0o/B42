cmake_minimum_required(VERSION 3.10)
project(Philosophers)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -g")

include_directories(include)

file(GLOB SOURCES
        "src/*.c"
        "src/functional/*.c"
        "src/utils/*.c"
        )
add_executable(philosophers ${SOURCES})