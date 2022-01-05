cmake_minimum_required(VERSION 3.20)
project(tutorLogging)

set(CMAKE_CXX_STANDARD 14)

add_executable(tutorLogging main.cpp Files/files_windows.cpp Files/files_linux.cpp Student.hpp Files/files_all.cpp)