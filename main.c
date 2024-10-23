//
// Created by cissy on 2024/10/17.
//
#include <stdio.h>
#include "screen.h"
#include "action.h"
#include "snack.h"
#include <time.h>
#include <sys/time.h>

struct UserActionContext{
    int Board_Length;
    int Board_Height;
    enum Direction dir;
    char **board;
};

void HandleUserAction(struct UserActionContext *ctx){
    enum Key key = GetKeyPressedInfo();
    if(key == W){
        ctx->dir = Up;
    }
    else if(key == S){
        ctx->dir = Down;
    }
    else if(key == D){
        ctx->dir = Right;
    }
    else if(key == A){
        ctx->dir = Left;
    }
    else{
        ctx->dir = None;
    }
}
// 获取当前时间（单位：毫秒）
long long current_time_millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000); // 转换为毫秒
}

int main() {

    srand(time(NULL)); // 设置种子
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    struct UserActionContext ctx;

    GameBegin(hStdout, &ctx.Board_Height, &ctx.Board_Length, &ctx.board);
    WaitGameStart();
    InitGame();

    // 初始化回合相关参数
    long long TimeInterval = 100; // 设定速度——时间间隔（单位：毫秒）
    long long round_begin = current_time_millis(); // 回合开始时间
    long long round_end; // 回合结束时间
    long long time_interval = TimeInterval; // 时间间隔判定
    while(1){
        // 回合开始
        // 处理用户动作
        HandleUserAction(&ctx);
        if(time_interval >= TimeInterval){
            // 贪吃蛇游戏
            bool gaming = SnackGame(ctx.dir, &ctx.board, ctx.Board_Length, ctx.Board_Height);
            if(!gaming){
                GameOver(hStdout, ctx.Board_Height, &ctx.board);
                break;
            }
            // 刷新屏幕
            RefreshGameBoard(hStdout, ctx.board);
            // 更新回合开始时间
            round_begin = current_time_millis();
        }

        // 回合结束时间
        round_end = current_time_millis();
        // 计算时间间隔
        time_interval = round_end - round_begin;
    }
    return 0;
}