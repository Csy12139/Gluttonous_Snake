//
// Created by cissy on 2024/10/20.
//

#ifndef GLUTTONOUS_SNAKE_SCREEN_H
#define GLUTTONOUS_SNAKE_SCREEN_H

#include <windows.h>
#include "array.h"

// 隐藏光标
void hide_cursor();

// 显示光标
void show_cursor();

// 在光标(cursor_x, cursor_y)处写入字符串
static CONSOLE_SCREEN_BUFFER_INFO Board_Write_String(HANDLE hStdout, int cursor_x, int cursor_y, char *content);

// 在光标(cursor_x, cursor_y)处写入字符
static CONSOLE_SCREEN_BUFFER_INFO Board_Write_Char(HANDLE hStdout, int cursor_x, int cursor_y, char content);

// 刷新屏幕
void RefreshScreen(HANDLE hStdout, struct TwoDimensionalArray board);


#endif //GLUTTONOUS_SNAKE_SCREEN_H
