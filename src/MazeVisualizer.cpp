//
// Created by Jeremy on 2/19/2021.
//

#include "MazeVisualizer.h"
#include <iostream>

// Is operating system windows?
// ConsoleCanvas is windows-only
#ifdef _WIN32

#include "ConsoleCanvas.h"

bool MazeVisualizer::visualize(Maze& maze, int delay) {
    if (maze.getWidth() > SHRT_MAX || maze.getHeight() > SHRT_MAX) {
        std::cout << "Maze is too large to be visualized in the console." << std::endl;
        return false;
    }
    ConsoleCanvas canvas = ConsoleCanvas("Maze Solver", (short) maze.getWidth(), (short) maze.getHeight());
    if (!canvas.create()) return false;
    canvas.setBackgroundColor(0);
    if (!canvas.fill()) return false;

    // Draw maze walls to console canvas
    canvas.setBackgroundColor(BACKGROUND_BLUE);
    for (short i = 0; i < (short) maze.getHeight(); i++) {
        for (short j = 0; j < (short) maze.getWidth(); j++) {
            if (maze.isSolid({j, i})) {
                if (!canvas.drawDot(j, i)) return false;
            }
        }
    }

    // Step through maze, draw state of maze on each iteration
    maze.begin();
    while (!maze.step()) {
        for (int y = 0; y < maze.getHeight(); y++) {
            for (int x = 0; x < maze.getWidth(); x++) {
                if (maze.isPath({x, y})) {
                    canvas.setBackgroundColor(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    if (!canvas.drawDot((short) x, (short) y)) return false;
                } else if (maze.isChecked({x, y})) {
                    canvas.setBackgroundColor(BACKGROUND_INTENSITY);
                    if (!canvas.drawDot((short) x, (short) y)) return false;
                }
            }
        }
        Sleep(delay);
    }
    // Wait for 5 seconds before ending the visualization.
    Sleep(5000);
    return canvas.destroy();
}

#else

bool MazeVisualizer::visualize(Maze& maze) {
    std::cout << "Maze visualization is only implemented for windows." << std::endl;
    return false;
}

#endif
