cmake_minimum_required(VERSION 3.28)
project(GoogleTestAndDebugging)

set(CMAKE_CXX_STANDARD 20)
set(CXX_WARNINGS -Wall -Werror -Wextra)
add_subdirectory(src)
add_subdirectory(testing)
