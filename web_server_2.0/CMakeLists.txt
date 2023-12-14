cmake_minimum_required(VERSION 2.8)

project(web_server_2.0 CXX)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CXX_FLAGS
   -g
   -pthread 
   -lmysqlclient 
   -w
)

add_subdirectory(src bin)
