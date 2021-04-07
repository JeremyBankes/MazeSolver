//
// Created by Jeremy on 2/18/2021.
//

#ifndef MAZE_H
#define MAZE_H

#include "MazePositionStack.h"

class Maze {

    private:
        bool* data;
        int width;
        int height;

        MazePosition end;

        // Stores the running solution.
        MazePositionStack path;
        // Stores cells that have been checked.
        MazePositionStack checked;

    public:
        Maze();

        virtual ~Maze();

        // Populate maze with a file in the delorie ascii format
        // Returns true if successful, false otherwise.
        bool read(const char* filename);

        // Write the current solution (path) to a file
        // Returns true if successful, false otherwise.
        bool write(const char* filename);

        // Attempts to solve the maze.
        // Returns true if successful, false otherwise.
        bool solve();

        // Prepare to start stepping through the maze.
        // Calling this method will clear the current state of the maze and start from the beginning.
        void begin();

        // Step through the maze, this will either add a new cell to the solution (path) or pop one off
        // if a dead end is reached. This method is designed to be called repetitively until it returns false
        // indicating one of the following scenarios:
        //      - every cell in the maze has been checked (checked stack contains all cells)
        //      - the maze has been solved (the end MazePosition is in path)
        bool step();

        // Returns true if position in path, false otherwise.
        bool isPath(const MazePosition& position);

        // Returns true if position in checked, false otherwise.
        bool isChecked(const MazePosition& position);

        // Returns true if position is a wall, false otherwise.
        bool isSolid(const MazePosition& position);

        // Returns true if a given tile is considered a valid step, false otherwise.
        bool isValidStep(const MazePosition& position);

        inline int getWidth() const { return width; }

        inline int getHeight() const { return height; }

};

#endif
