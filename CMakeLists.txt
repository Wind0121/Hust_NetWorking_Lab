cmake_minimum_required(VERSION 3.26)
project(1)

set(CMAKE_CXX_STANDARD 17)

#添加头文件搜索路径
include_directories(C:\\mingw64\\include)
#添加库文件搜索路径
link_directories(C:\\mingw64\\lib)
link_libraries(ws2_32)
add_executable(1 main.cpp)
target_link_libraries(1 ws2_32)
