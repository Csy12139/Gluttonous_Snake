//
// Created by cissy on 2024/10/20.
//
#include <stdbool.h>
#include <windows.h>
#ifndef GLUTTONOUS_SNAKE_ACTION_H
#define GLUTTONOUS_SNAKE_ACTION_H
enum Key{
    W = 2,
    S = 3,
    D = 4,
    A = 5,
    SPACE =6, // 空格
};

// 键'key'是否被按下
bool IsKeyPressed(int key);
// 返回哪个键被按下
enum Key GetKeyPressedInfo();
// 等待用户触发SPACEBAR，开始游戏
void WaitGameStart();

#endif //GLUTTONOUS_SNAKE_ACTION_H
