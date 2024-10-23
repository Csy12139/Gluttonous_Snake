//
// Created by cissy on 2024/10/20.
//
#include "action.h"

// 键'key'是否被按下
bool IsKeyPressed(int key){
    return (GetAsyncKeyState(key) & 0x8000);
}

// 返回哪个键被按下
enum Key GetKeyPressedInfo(){
    enum Key key;
    if (IsKeyPressed('W')) {
        key = W;
    }
    else if (IsKeyPressed('A')) {
        key = A;
    }
    else if (IsKeyPressed('S')) {
        key = S;
    }
    else if (IsKeyPressed('D')) {
        key = D;
    }
    else if (IsKeyPressed(VK_SPACE)) {
        key = SPACE;
    }
    return key;
}

// 等待用户触发SPACEBAR 开始游戏
void WaitGameStart(){
    while(1){
        if(IsKeyPressed(VK_SPACE)){
            break;
        }
    }
}