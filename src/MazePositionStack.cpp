//
// Created by Jeremy on 2/18/2021.
//

#include "MazePositionStack.h"
#include <iostream>

MazePositionStack::MazePositionStack() : first(nullptr), last(nullptr) {
}

MazePositionStack::~MazePositionStack() {
    clear();
}

void MazePositionStack::push(const MazePosition& position) {
    MazePositionNode* node = new MazePositionNode{last, nullptr, position};
    if (last == nullptr) {
        // The only node in the stack
        first = last = node;
    } else {
        // Append the node onto the end of the stack.
        last->child = node;
        node->parent = last;
        last = node;
    }
}

MazePosition MazePositionStack::pop() {
    // Keep a local copy of last (So it can be deleted)
    MazePositionNode* node = last;
    MazePosition position = node->position;
    // Make our last node the former second last node
    last = last->parent;
    if (last == nullptr) {
        // There is no second last node, stack is empty
        first = nullptr;
    } else {
        // Ensure the new last doesn't have a child
        last->child = nullptr;
    }
    delete node;
    return position;
}

MazePosition MazePositionStack::peek() {
    return last->position;
}

bool MazePositionStack::isEmpty() {
    return last == nullptr;
}

bool MazePositionStack::contains(const MazePosition& position) {
    MazePositionNode* node = first;
    while (node) {
        if (IS_POSITION_EQUAL(node->position, position)) return true;
        node = node->child;
    }
    return false;
}

void MazePositionStack::clear() {
    while (first) pop();
}


