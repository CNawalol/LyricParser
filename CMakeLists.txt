cmake_minimum_required(VERSION 3.26)
project(LyricParser)

set(CMAKE_CXX_STANDARD 23)

add_executable(LyricParser src/main.cpp
        src/qrc/Line.h
        src/qrc/Word.h
        src/qrc/LyricParser.cpp
        src/qrc/LyricParser.h
)
