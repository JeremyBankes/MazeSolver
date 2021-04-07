//
// Created by Jeremy on 2/18/2021.
//

#include "Maze.h"
#include <fstream>
#include <cstring>

#include <iostream>

#define MAXIMUM_MAZE_SIZE 128


Maze::Maze() : data(nullptr), width(0), height(0), end({0, 0}) {}

Maze::~Maze() {
    delete[] data;
}

// Populating our maze data attribute requires two passes through our input file as to allow for doing only one heap allocation.
// This is because the dimensions for our maze are required to allocate memory, but memory has to be allocated to store our maze.
bool Maze::read(const char* filename) {
    int bufferSize;
    char buffer[MAXIMUM_MAZE_SIZE];
    std::ifstream inputStream(filename);
    if (!inputStream.is_open()) return false;
    // The first pass over the input file just determine the dimensions of the maze.
    while (inputStream.good()) {
        inputStream.getline(buffer, MAXIMUM_MAZE_SIZE);
        bufferSize = strlen(buffer);
        if (bufferSize > width) width = bufferSize;
        height++;
    }
    // with the dimensions, an allocation can be done.
    data = new bool[width * height];
    // reuse the input stream (seek back to beginning)
    inputStream.seekg(0);
    // The second pass over the input file will store the maze data in the newly allocated memory.
    for (int i = 0; i < height; i++) {
        inputStream.getline(buffer, MAXIMUM_MAZE_SIZE);
        bufferSize = strlen(buffer);
        for (int j = 0; j < width; j++) {
            data[i * width + j] = j < bufferSize && buffer[j] != ' ';
        }
    }
    return true;
}

bool Maze::write(const char* filename) {
    char buffer[MAXIMUM_MAZE_SIZE];
    memset(buffer, '\0', MAXIMUM_MAZE_SIZE);
    std::ofstream outputStream(filename);
    if (!outputStream.is_open()) return false;
    MazePosition position;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            position = {j, i};
            if (isSolid(position)) {
                // Lots of disgusting ternaries to choose '+', '-' or '|' based on the parity
                // of our current row and column.
                buffer[j] = (i % 2 == 0 ? (j % 2 == 0 ? '+' : '-') : '|');
            } else if (isPath(position)) {
                buffer[j] = '#';
            } else {
                buffer[j] = ' ';
            }
        }
        outputStream << buffer << std::endl;
    }
    outputStream.close();
    return true;
}

bool Maze::solve() {
    begin();
    while (!step());
    return path.contains(end);
}

void Maze::begin() {
    path.clear();
    checked.clear();
    end = {width - 1, height - 1 - 1};
    path.push({0, 1});
}

bool Maze::step() {
    const MazePosition current = path.peek();
    MazePosition north = {current.x, current.y - 1};
    MazePosition east = {current.x + 1, current.y};
    MazePosition south = {current.x, current.y + 1};
    MazePosition west = {current.x - 1, current.y};

    // Attempt to take a step in one of the cardinal directions.
    if (isValidStep(south)) path.push(south);
    else if (isValidStep(east)) path.push(east);
    else if (isValidStep(west)) path.push(west);
    else if (isValidStep(north)) path.push(north);
    // Unless the current position is the end of the maze, we've hit a dead end, step backwards.
    else if (!IS_POSITION_EQUAL(current, end)) path.pop();

    if (!checked.contains(current)) checked.push(current);

    return path.isEmpty() || IS_POSITION_EQUAL(current, end);
}

bool Maze::isPath(const MazePosition& position) {
    return path.contains(position);
}

bool Maze::isChecked(const MazePosition& position) {
    return checked.contains(position);
}


bool Maze::isSolid(const MazePosition& position) {
    return data[position.y * width + position.x];
}

// step is valid if:
//  - in correct bounds (more than 0, less than width and height)
//  - is not into a wall
//  - haven't already checked cell
bool Maze::isValidStep(const MazePosition& position) {
    if (position.x < 0 || position.y < 0 || position.x >= width || position.y >= height) return false;
    if (isSolid(position)) return false;
    if (isChecked(position)) return false;
    return true;
}




