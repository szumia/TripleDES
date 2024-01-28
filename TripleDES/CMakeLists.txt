cmake_minimum_required(VERSION 3.26)
project(TripleDES)

set(CMAKE_CXX_STANDARD 17)

add_executable(TripleDES main.cpp
        Des.h
        TripleDes.h
        TypeTransform.h
)
