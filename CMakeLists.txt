cmake_minimum_required(VERSION 3.10)
project(uo)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE ff)