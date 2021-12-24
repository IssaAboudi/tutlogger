cmake_minimum_required(VERSION 3.20)
project(tutorLogging)

set(CMAKE_CXX_STANDARD 14)

add_executable(tutorLogging main.cpp tutee_windows.cpp tutee_linux.cpp)
