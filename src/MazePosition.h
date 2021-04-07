//
// Created by Jeremy on 2/18/2021.
//

#ifndef MAZE_POSITION_H
#define MAZE_POSITION_H

// In attempt to avoid putting methods in structs. Should MazePosition be a class?
#define IS_POSITION_EQUAL(positionA, positionB) (positionA.x == positionB.x && positionA.y == positionB.y)

struct MazePosition {

    int x, y;

};

#endif
