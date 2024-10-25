//
// Created by cissy on 2024/10/20.
//

#include "screen.h"
#include <stdio.h>
#include "array.h"

// 隐藏光标
void hide_cursor() {
    printf("\033[?25l");
    fflush(stdout);
}

// 显示光标
void show_cursor() {
    printf("\033[?25h");
    fflush(stdout);
}

// 在光标(cursor_x, cursor_y)处写入字符串
static CONSOLE_SCREEN_BUFFER_INFO Board_Write_String(HANDLE hStdout, int cursor_x, int cursor_y, char *content) {
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
static CONSOLE_SCREEN_BUFFER_INFO Board_Write_Char(HANDLE hStdout, int cursor_x, int cursor_y, char content) {
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo); // 获取当前光标位置
    COORD newCursorPosition = {cursor_x, cursor_y}; // 设置光标位置
    SetConsoleCursorPosition(hStdout, newCursorPosition); // 移动光标
    printf("%c", content);
    fflush(stdout);
//    SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition); //恢复光标位置
    return csbiInfo;
}

// 刷新屏幕
void RefreshScreen(HANDLE hStdout, struct TwoDimensionalArray board) {
    for (int i = 0; i < board.Height; i++) {
        for (int j = 0; j < board.Length; j++) {
            Board_Write_Char(hStdout, j, i, board.Array[i][j]);
        }
    }
}


