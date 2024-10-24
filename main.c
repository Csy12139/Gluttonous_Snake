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
#include "context.h"

void HandleUserAction(struct UserActionContext *ctx) {
    enum Key key = GetKeyPressedInfo();
    if (key == W) {
        ctx->dir = Up;
    } else if (key == S) {
        ctx->dir = Down;
    } else if (key == D) {
        ctx->dir = Right;
    } else if (key == A) {
        ctx->dir = Left;
    } else {
        ctx->dir = None;
    }
}

// 获取当前时间（单位：毫秒）
uint64_t current_time_millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000); // 转换为毫秒
}

int main() {
    srand(time(NULL)); // 设置种子
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    extern struct UserActionContext ctx;

    GameBegin(hStdout, &ctx);
    WaitGameStart();
    InitGame();

    // 初始化回合相关参数
    uint64_t TimeInterval = 100; // 设定速度——时间间隔（单位：毫秒）
    uint64_t last_round_timestamp = current_time_millis();
    while (1) {
        // 回合开始
        // 处理用户动作
        HandleUserAction(&ctx);
        if (current_time_millis() - last_round_timestamp >= TimeInterval) {
            // 贪吃蛇游戏
            bool gaming = SnackGame(&ctx);
            if (!gaming) {
                GameOver(hStdout, &ctx);
                break;
            }
            // 刷新屏幕
            RefreshGameBoard(hStdout, ctx);
            // 更新回合开始时间
            last_round_timestamp = current_time_millis();
        }
    }
    return 0;
}