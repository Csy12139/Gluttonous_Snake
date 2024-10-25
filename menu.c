//
// Created by cissy on 2024/10/25.
//
# include "menu.h"
#include "array.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

static int Screen_Height = 20;
static int Screen_Length = 100;

// 游戏开始
void GameMenu(struct TwoDimensionalArray *board) {
    GameTips(board, board->Height / 3, board->Length / 3 + 9, "-- GameMenu --");
    GameTips(board, board->Height / 3 + 2, board->Length / 3 + 8, "Gluttonous Snake");
    GameTips(board, board->Height / 3 + 4, board->Length / 3, "~~ Press the 'space' to start ~~");
}

// 游戏结束提示语
void GameOverTips(struct TwoDimensionalArray *board) {
    GameTips(board, board->Height / 3 + 2, board->Length / 3 + 8, "~~ Game Over ~~");
}

// 创建菜单界面
void CreatMenuBoard(struct TwoDimensionalArray *board) {
    board->Height = Screen_Height;
    board->Length = Screen_Length;
    board->Array = malloc(board->Height * sizeof(char *));
    for (int i = 0; i < board->Height; i++) {
        board->Array[i] = malloc(board->Length * sizeof(char));
    }
    for (int i = 0; i < board->Height; i++) {
        for (int j = 0; j < board->Length; j++) {
            if (i == 0 || i == board->Height - 1) {
                board->Array[i][j] = '-';
            } else if (j == 0 || j == board->Length - 1) {
                board->Array[i][j] = '|';
            } else {
                board->Array[i][j] = ' ';
            }
        }
    }
}

// 删除菜单界面
void DeleteMenuBoard(struct TwoDimensionalArray *board) {
    for (int i = 0; i < board->Height; i++) {
        free(board->Array[i]);
    }
    free(board->Array);
}

// 游戏提示语
void GameTips(struct TwoDimensionalArray *board, int x, int y, const char *content) {
    uint64_t content_length = strlen(content);
    strncpy(&board->Array[x][y], content, content_length);
}

// 清屏
void ClearMenuBoard(struct TwoDimensionalArray *board) {
    for (int i = 1; i < board->Height - 1; i++) {
        for (int j = 1; j < board->Length - 1; j++) {
            board->Array[i][j] = ' ';
        }
    }
}