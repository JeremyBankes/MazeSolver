//
// Created by Jeremy on 2/21/2021.
//

#include <iostream>
#include <sstream>
#include "Application.h"
#include "MazeVisualizer.h"

bool Application::run(int argumentCount, char** arguments) {
    if (argumentCount < 2) {
        std::cout << "Missing required first argument. (path to maze file)" << std::endl;
        return false;
    }
    int delay = 100;
    if (argumentCount >= 3) {
        std::string delayArgument = std::string(arguments[2]);
        std::stringstream stream(delayArgument);
        stream >> delay;
        if (!stream) {
            std::cout << "Failed to parse second argument as an integral value." << std::endl;
            return false;
        }
    }
    bool solved;
    Maze maze;
    std::cout << "Reading maze file \"" << arguments[1] << "\"." << std::endl;
    if (!maze.read(arguments[1])) {
        std::cout << "Failed to read maze file. Please ensure that the given maze file is in the delorie ascii format." << std::endl;
        std::cout << "\thttp://www.delorie.com/game-room/mazes/genmaze.cgi" << std::endl;
        return false;
    }
    if (!(solved = MazeVisualizer::visualize(maze, delay))) {
        std::cout << "Maze visualization failed, solving without visualization." << std::endl;
        solved = maze.solve();
    }
    if (!maze.write("./solution.txt")) {
        std::cout << "Failed to write maze solution file." << std::endl;
        return false;
    }
    return solved;
}
