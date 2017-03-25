cmake_policy(VERSION 2.6)
project(crossguid)

if(APPLE)
    add_definitions(-DGUID_CFUUID)
endif(APPLE)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_definitions(-DGUID_LIBUUID)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

add_library(crossguid STATIC guid.h guid.cpp)
