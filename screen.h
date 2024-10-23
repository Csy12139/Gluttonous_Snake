//
// Created by cissy on 2024/10/20.
//
#include <windows.h>
#include <stdio.h>
#ifndef GLUTTONOUS_SNAKE_SCREEN_H
#define GLUTTONOUS_SNAKE_SCREEN_H

// 隐藏光标
void HideCursor();
// 显示光标
void show_cursor();
// 在光标(cursor_x, cursor_y)处写入字符串
CONSOLE_SCREEN_BUFFER_INFO Board_Write_String(HANDLE hStdout, int cursor_x, int cursor_y, char *content);
// 在光标(cursor_x, cursor_y)处写入字符
CONSOLE_SCREEN_BUFFER_INFO Board_Write_Char(HANDLE hStdout, int cursor_x, int cursor_y, char content);
// 创建游戏界面
void CreatGameBoard(int *Board_Height, int *Board_Length, char ***board);
// 删除游戏界面
void DeleteGameBoard(int Board_Height, char ***board);
// 游戏开始提示语
void GameBeginInfo(HANDLE hStdout);
// 游戏结束提示语
void GameOverInfo(HANDLE hStdout);
// 清屏-游戏屏幕
void ClearGameBoard(char ***board);
// 刷新游戏界面
void RefreshGameBoard(HANDLE hStdout, char **board);
// 刷新整个屏幕
void RefreshScreen(HANDLE hStdout, char **board);
// 游戏开始
void GameBegin(HANDLE hStdout, int *Board_Height, int *Board_Length, char ***board);
// 游戏结束
void GameOver(HANDLE hStdout, int Board_Height, char ***board);
#endif //GLUTTONOUS_SNAKE_SCREEN_H
