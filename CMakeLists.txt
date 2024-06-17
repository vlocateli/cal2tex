cmake_minimum_required(VERSION 3.10)

project(psyche VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_executable(psyche src/main.cc)

target_compile_options(psyche PUBLIC -Wall -Wextra -Werror -pedantic -std=c++17 -march=native -O1 -ggdb)
target_link_libraries(psyche PRIVATE -fsanitize=address,undefined)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON ) 
file(COPY ${data} DESTINATION resource)




target_link_libraries(psyche PRIVATE ical )

