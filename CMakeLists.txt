cmake_minimum_required(VERSION 3.16)
project(synthesis)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

add_executable(Filesystem Filesystem.cc
        include/Element.h
        include/View.h src/View.cc
        include/Folder.h src/Folder.cc
        include/FastView.h src/FastView.cc)
