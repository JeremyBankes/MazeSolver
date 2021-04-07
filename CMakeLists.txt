cmake_minimum_required(VERSION 3.17)
project(Assignment2)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        solve

        src/main.cpp

        src/Application.h
        src/Application.cpp

        src/Maze.h
        src/Maze.cpp

        src/MazePosition.h

        src/MazePositionStack.h
        src/MazePositionStack.cpp

        src/MazeVisualizer.h
        src/MazeVisualizer.cpp

        src/ConsoleCanvas.h
        src/ConsoleCanvas.cpp

        src/WindowsTools.h
        src/WindowsTools.cpp
)