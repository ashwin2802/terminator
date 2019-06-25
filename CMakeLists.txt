cmake_minimum_required(VERSION 2.8.3)
project(executor)

find_package(catkin REQUIRED)
find_package(catkin_simple REQUIRED)
catkin_simple()

add_definitions(-std=c++11)
set(CMAKE_BUILD_TYPE Release)

cs_add_executable(server src/server.cpp)
cs_add_executable(publisher src/publisher.cpp)
cs_add_executable(client src/client.cpp)

cs_install()
cs_export()