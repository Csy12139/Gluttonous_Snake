//
// Created by cissy on 2024/10/17.
//
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include "screen.h"
#include "action.h"
#include "snack.h"
#include "menu.h"
#include "array.h"

// 处理用户操作——按键转换为方向
enum Direction HandleUserAction() {
    enum Key key = GetKeyPressedInfo();
    if (key == W) {
        return Up;
    } else if (key == S) {
        return Down;
    } else if (key == D) {
        return Right;
    } else if (key == A) {
        return Left;
    } else {
        return None;
    }
}

// 获取当前时间（单位：毫秒）
uint64_t current_time_millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000); // 转换为毫秒
}

// 游戏准备开始
void GameReadyToStart(HANDLE hStdout, struct TwoDimensionalArray *board) {
    hide_cursor(); // 隐藏光标

    CreatMenuBoard(board);
    GameMenu(board); // 游戏菜单
    RefreshScreen(hStdout, *board);

    WaitGameStart(); // 等待用户确认开始

    ClearMenuBoard(board); // 清屏
    RefreshScreen(hStdout, *board);

    InitSnackGame(); // 初始化贪吃蛇
}

// 游戏结束
void GameOver(HANDLE hStdout, struct TwoDimensionalArray *board) {
    ClearMenuBoard(board); // 清屏
    GameOverTips(board); // 游戏结束提示语
    RefreshScreen(hStdout, *board);
    DeleteMenuBoard(board);
    show_cursor(); // 显示光标
}

int main() {
    srand(time(NULL)); // 设置种子
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    struct TwoDimensionalArray *board = (struct TwoDimensionalArray *) malloc(sizeof(struct TwoDimensionalArray));

    // 游戏准备开始
    GameReadyToStart(hStdout, board);

    // 初始化回合相关参数
    uint64_t TimeInterval = 100; // 设定速度——时间间隔（单位：毫秒）
    uint64_t last_round_timestamp = current_time_millis();
    while (1) {
        // 回合开始
        // 处理用户动作
        enum Direction dir = HandleUserAction();
        if (current_time_millis() - last_round_timestamp >= TimeInterval) {
            // 贪吃蛇游戏
            bool gaming = SnackGame(board, dir);
            if (!gaming) {
                GameOver(hStdout, board); // 游戏结束
                break;
            }
            // 刷新屏幕
            RefreshScreen(hStdout, *board);
            // 更新回合开始时间
            last_round_timestamp = current_time_millis();
        }
    }

    free(board);
    return 0;
}