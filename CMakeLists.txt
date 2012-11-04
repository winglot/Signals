cmake_minimum_required(VERSION 2.8)

project(VarSlot)

include_directories("include")

set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -fPIC -flto -O2")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})

add_library(VarSlot SHARED src/W_Slot.cpp)
add_library(VarSlot_static STATIC src/W_Slot.cpp)
