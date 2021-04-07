//
// Created by Jeremy on 2/19/2021.
//

#ifndef MAZE_VISUALIZER_H
#define MAZE_VISUALIZER_H

#include "Maze.h"

class MazeVisualizer {

    public:

        // Visualizes the solving of a given maze. (blocking)
        // The delay attributes specifies how long to wait between each step in milliseconds.
        // Returns true if the visualization is successful, false otherwise.
        bool static visualize(Maze& maze, int delay);

};

#endif
