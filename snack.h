//
// Created by cissy on 2024/10/20.
//

#ifndef GLUTTONOUS_SNAKE_SNACK_H
#define GLUTTONOUS_SNAKE_SNACK_H

#include <stdbool.h>

extern struct UserActionContext ctx;

enum Direction {
    Up = 2,
    Down = 3,
    Right = 4,
    Left = 5,
    None = 6,
};
struct Snack { // 蛇
    int length; // 蛇的长度
    int body_direction[20 * 100]; // 蛇身的方向
    int head_x; // 蛇头x坐标
    int head_y; // 蛇头y坐标
    int tail_x; // 蛇尾x坐标
    int tail_y; // 蛇尾y坐标
    int head_direction; // 蛇头方向
};
struct Move {
    int X;
    int Y;
};
struct Fruit { // 果实
    int X;
    int Y;
};

// 初始化游戏
void InitGame();

// 随机生成果实
void GenerateFruit(struct UserActionContext *ctx);

// 获取移动步长
struct Move GetMoveStep(enum Direction dir);
// 贪吃蛇游戏
bool SnackGame(struct UserActionContext *ctx);

#endif //GLUTTONOUS_SNAKE_SNACK_H
