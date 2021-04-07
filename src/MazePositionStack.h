//
// Created by Jeremy on 2/18/2021.
//

#ifndef MAZE_POSITION_STACK_H
#define MAZE_POSITION_STACK_H

#include "MazePosition.h"

// A node for storing the position of a MazePosition in a stack
struct MazePositionNode {

    MazePositionNode* parent;
    MazePositionNode* child;
    MazePosition position;

};

// A bare-bones stack implementation for MazePositions
class MazePositionStack {

    private:
        MazePositionNode* first;
        MazePositionNode* last;

    public:

        MazePositionStack();

        virtual ~MazePositionStack();

        void push(const MazePosition& position);

        MazePosition pop();

        MazePosition peek();

        void clear();

        bool isEmpty();

        bool contains(const MazePosition& position);
};

#endif
