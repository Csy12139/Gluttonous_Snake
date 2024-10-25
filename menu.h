//
// Created by cissy on 2024/10/25.
//

#ifndef GLUTTONOUS_SNAKE_MENU_H
#define GLUTTONOUS_SNAKE_MENU_H

#include "array.h"

// 游戏菜单
void GameMenu(struct TwoDimensionalArray *board);

// 游戏结束提示语
void GameOverTips(struct TwoDimensionalArray *board);

// 创建菜单界面
void CreatMenuBoard(struct TwoDimensionalArray *board);

// 删除菜单界面
void DeleteMenuBoard(struct TwoDimensionalArray *board);

// 游戏提示语
void GameTips(struct TwoDimensionalArray *board, int x, int y, const char *content);

// 清屏
void ClearMenuBoard(struct TwoDimensionalArray *board);

#endif //GLUTTONOUS_SNAKE_MENU_H
