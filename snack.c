//
// Created by cissy on 2024/10/20.
//
#include "snack.h"
#include <stdlib.h>
#include "array.h"

static struct Snack snack;
static struct Fruit fruit;

// 初始化游戏
void InitSnackGame() {
    snack.length = 1;
    snack.head_x = 1;
    snack.head_y = 1;
    snack.tail_x = 1;
    snack.tail_y = 1;
    snack.head_direction = Right;
    snack.body_direction[0] = snack.head_direction;
}

// 随机生成果实
void GenerateFruit(struct TwoDimensionalArray *board) {

    if (board->Array[fruit.Y][fruit.X] != '$') { //果实被吃掉了
        while (1) {
            // int randomNumber = rand() % (max - min + 1) + min;
            int random_X = rand() % ((board->Length - 2) - 1 + 1) + 1;
            int random_Y = rand() % ((board->Height - 2) - 1 + 1) + 1;
            if (board->Array[random_Y][random_X] != '@') {
                fruit.X = random_X;
                fruit.Y = random_Y;
                board->Array[fruit.Y][fruit.X] = '$';
                break;
            }
        }
    }
}

// 获取移动步长
struct Move GetMoveStep(enum Direction dir) {
    struct Move move;
    move.X = 0;
    move.Y = 0;
    if (dir == Up) {
        move.Y -= 1;
    } else if (dir == Down) {
        move.Y += 1;
    } else if (dir == Left) {
        move.X -= 1;
    } else if (dir == Right) {
        move.X += 1;
    }
    return move;
}

// 贪吃蛇游戏
bool SnackGame(struct TwoDimensionalArray *board, enum Direction dir) {

    // 随机生成果实
    GenerateFruit(board);
    // 如果方向改变-->更新方向
    if (dir != None) snack.head_direction = dir;
    // 获取移动步长
    struct Move move_head = GetMoveStep(snack.head_direction);
    // 移动蛇头
    snack.head_x += move_head.X;
    snack.head_y += move_head.Y;
    board->Array[snack.head_y][snack.head_x] = '@';
    // 判断是否过界
    if (snack.head_x <= 0 || snack.head_y <= 0 || snack.head_x >= board->Length - 1 ||
        snack.head_y >= board->Height - 1) {
        return false;
    }
    // 更新蛇身方向
    for (int i = 0; i < snack.length - 1; i++) {
        snack.body_direction[i] = snack.body_direction[i + 1];
    }
    // 更新蛇头方向
    snack.body_direction[snack.length - 1] = snack.head_direction;
    board->Array[snack.head_y][snack.head_x] = '@';
    // 如果吃到果实
    if (snack.head_y == fruit.Y && snack.head_x == fruit.X) {
        snack.head_x += move_head.X;
        snack.head_y += move_head.Y;
        board->Array[snack.head_y][snack.head_x] = '@';
        snack.length += 1; // 蛇长度+1
        snack.body_direction[snack.length - 1] = snack.head_direction; // 更新蛇头方向
    }
    // 移动蛇尾
    board->Array[snack.tail_y][snack.tail_x] = ' ';
    struct Move move_tail = GetMoveStep(snack.body_direction[0]);
    snack.tail_x += move_tail.X;
    snack.tail_y += move_tail.Y;

    return true;
}