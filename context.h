//
// Created by cissy on 2024/10/24.
//
#ifndef GLUTTONOUS_SNAKE_CONTEXT_H
#define GLUTTONOUS_SNAKE_CONTEXT_H

#include "snack.h"

struct UserActionContext {
    int Board_Length;
    int Board_Height;
    enum Direction dir;
    char **board;
};
//extern struct UserActionContext ctx;

#endif //GLUTTONOUS_SNAKE_CONTEXT_H
