//
// Created by cissy on 2024/10/20.
//

#include "screen.h"
#include "context.h"
#include <stdio.h>

static int Screen_Height = 20;
static int Screen_Length = 100;

// 隐藏光标
void HideCursor() {
    printf("\033[?25l");
    fflush(stdout);
}

// 显示光标
void show_cursor() {
    printf("\033[?25h");
    fflush(stdout);
}

// 在光标(cursor_x, cursor_y)处写入字符串
CONSOLE_SCREEN_BUFFER_INFO Board_Write_String(HANDLE hStdout, int cursor_x, int cursor_y, char *content) {
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo); // 获取当前光标位置
    COORD newCursorPosition = {cursor_x, cursor_y}; // 设置光标位置
    SetConsoleCursorPosition(hStdout, newCursorPosition); // 移动光标
    printf("%s", content);
    fflush(stdout);
//    SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition); //恢复光标位置
    return csbiInfo;
}

// 在光标(cursor_x, cursor_y)处写入字符
CONSOLE_SCREEN_BUFFER_INFO Board_Write_Char(HANDLE hStdout, int cursor_x, int cursor_y, char content) {
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo); // 获取当前光标位置
    COORD newCursorPosition = {cursor_x, cursor_y}; // 设置光标位置
    SetConsoleCursorPosition(hStdout, newCursorPosition); // 移动光标
    printf("%c", content);
    fflush(stdout);
//    SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition); //恢复光标位置
    return csbiInfo;
}

// 创建游戏界面
void CreatGameBoard(struct UserActionContext *ctx) {
    (*ctx).Board_Height = Screen_Height;
    (*ctx).Board_Length = Screen_Length;
    (*ctx).board = malloc(Screen_Height * sizeof(char *));
    for (int i = 0; i < Screen_Height; i++) {
        (*ctx).board[i] = malloc(Screen_Length * sizeof(char));
    }
    for (int i = 0; i < Screen_Height; i++) {
        for (int j = 0; j < Screen_Length; j++) {
            if (i == 0 || i == Screen_Height - 1) {
                (*ctx).board[i][j] = '-';
            } else if (j == 0 || j == Screen_Length - 1) {
                (*ctx).board[i][j] = '|';
            } else {
                (*ctx).board[i][j] = ' ';
            }
        }
    }
}

// 删除游戏界面
void DeleteGameBoard(struct UserActionContext *ctx) {
    for (int i = 0; i < (*ctx).Board_Height; i++) {
        free((*ctx).board[i]);
    }
    free((*ctx).board);
}

// 游戏开始提示语
void GameBeginInfo(HANDLE hStdout) {
    Board_Write_String(hStdout, Screen_Length / 3, Screen_Height / 3, "***** Gluttonous Snake *****\n");
    Board_Write_String(hStdout, Screen_Length / 3, Screen_Height / 3 + 2, "Game Begin: Press 'SPACEBAR'.\n");
}

// 游戏结束提示语
void GameOverInfo(HANDLE hStdout) {
    Board_Write_String(hStdout, Screen_Length / 3, Screen_Height / 3 + 2, "~~~~~ Game Over! ~~~~~\n");
}

// 清屏-游戏屏幕
void ClearGameBoard(struct UserActionContext *ctx) {
    for (int i = 1; i < Screen_Height - 1; i++) {
        for (int j = 1; j < Screen_Length - 1; j++) {
            (*ctx).board[i][j] = ' ';
        }
    }
}

// 刷新游戏界面
void RefreshGameBoard(HANDLE hStdout, struct UserActionContext ctx) {

    for (int i = 1; i < Screen_Height - 1; i++) {
        for (int j = 1; j < Screen_Length - 1; j++) {

            Board_Write_Char(hStdout, j, i, ctx.board[i][j]);
        }
    }
}

// 刷新整个屏幕
void RefreshScreen(HANDLE hStdout, struct UserActionContext ctx) {
    for (int i = 0; i < Screen_Height; i++) {
        for (int j = 0; j < Screen_Length; j++) {
            Board_Write_Char(hStdout, j, i, ctx.board[i][j]);
        }
    }
}

// 游戏开始
void GameBegin(HANDLE hStdout, struct UserActionContext *ctx) {
    HideCursor(); // 隐藏光标
    CreatGameBoard(ctx);
    RefreshScreen(hStdout, *ctx);
    GameBeginInfo(hStdout);
}

// 游戏结束
void GameOver(HANDLE hStdout, struct UserActionContext *ctx) {
    ClearGameBoard(ctx);
    GameOverInfo(hStdout);
    DeleteGameBoard(ctx);
    show_cursor(); // 显示光标
}