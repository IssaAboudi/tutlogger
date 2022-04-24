cmake_minimum_required(VERSION 3.20)
project(tutorLogging)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_subdirectory(Ext/imgui)

set(FILES
        Files/files_windows.cpp
        Files/files_linux.cpp
        Files/files_all.cpp)

set(APPLICATION
        Application.cpp
        Application.hpp
        DebugMode.hpp
        )

add_executable(tutorLogging Ext/imgui/main.cpp ${APPLICATION} ${FILES} )

target_link_libraries(tutorLogging glad::glad glfw imgui_setup)