cmake_minimum_required(VERSION 3.10)

project(cal2tex VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_executable(cal2tex src/main.cpp src/cal2receipt.cpp)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
target_compile_options(cal2tex PUBLIC -Wall -Wextra -Werror -pedantic -std=c++17 -march=native -Os -ggdb)
target_link_libraries(cal2tex PRIVATE -fsanitize=address,undefined)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON ) 
file(COPY ${data} DESTINATION resource)




target_link_libraries(cal2tex PRIVATE ical )

