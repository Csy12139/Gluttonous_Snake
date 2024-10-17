//
// Created by cissy on 2024/10/17.
//
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
# define Board_Length 100
# define Board_Height 20
# define my_UP 2
# define my_DOWN 3
# define my_LEFT 4
# define my_RIGHT 5
char Board[Board_Height][Board_Length];
void GameBoard(){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newCursorPosition = {0, 0}; // 设置光标位置
    SetConsoleCursorPosition(hStdout, newCursorPosition); // 移动光标
    for(int i=0; i<Board_Height; i++){
        for(int j=0; j<Board_Length; j++)
        {
            if( i==0 || i==Board_Height-1){
                Board[i][j] = '-';
                printf("-");
            }
            else if(j==0 || j==Board_Length-1){
                Board[i][j] = '|';
                printf("|");
            }
            else {
                Board[i][j] = ' ';
                printf(" ");
            }
        }
        printf("\n");
    }
    fflush(stdout);
}
// 在光标(cursor_x, cursor_y)处写入content
void Board_Write(int cursor_x, int cursor_y, const char *content){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newCursorPosition = {cursor_x, cursor_y}; // 设置光标位置
    SetConsoleCursorPosition(hStdout, newCursorPosition); // 移动光标
    printf("%s", content);
    fflush(stdout);
}
// 在光标(cursor_x, cursor_y)处写入content后，回到原光标位置
void Board_Temporary_Write(int cursor_x, int cursor_y, const char *content){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo); // 获取当前光标位置
    COORD newCursorPosition = {cursor_x, cursor_y}; // 设置光标位置
    SetConsoleCursorPosition(hStdout, newCursorPosition); // 移动光标
    printf("%s", content);
    fflush(stdout);
    SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition); //恢复光标位置
}
void GameBegin(){
    GameBoard();
    Board_Temporary_Write(Board_Length/3, Board_Height/3, "***** Gluttonous Snake *****\n");
    Board_Temporary_Write(Board_Length/3, Board_Height/3+2, "Game Begin: Press 'SPACEBAR'.\n");
}
void GameOver(){
    GameBoard();
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo); // 获取当前光标位置
    COORD newCursorPosition_2 = {Board_Length/3, Board_Height/3+2}; // 移动光标
    SetConsoleCursorPosition(hStdout, newCursorPosition_2); // 设置光标
    printf("~~~~~ Game Over! ~~~~~\n");
    fflush(stdout);
    SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition); //恢复光标位置
}
void test(){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

//    COORD newCursorPosition_1 = {0, 0}; // 设置光标位置到 (0, 0)
//    SetConsoleCursorPosition(hStdout, newCursorPosition_1); // 移动光标
    printf("hello csy\n");
    printf("I'm fine.\n");
    printf("Please.\n");
    fflush(stdout);

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo1;
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo1); // 获取当前光标位
    COORD newCursorPosition_2 = {0, 0}; // 设置光标位置到 (0, 0)
    SetConsoleCursorPosition(hStdout, newCursorPosition_2); // 移动光标
    printf("H");
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo); // 获取当前光标位置

    printf("X");
    SetConsoleCursorPosition(hStdout, csbiInfo1.dwCursorPosition); //恢复光标位置
    while(1){}
}
int main() {
//    test();
    srand(time(NULL)); // 设置种子
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GameBegin();
    while(1){ // Game Begin ?
        short s = GetAsyncKeyState(0x20 ); // SPACEBAR
        if((s & 0x8000)){
            break;
        }
    }
    // 清屏
    COORD newCursorPosition_1 = {0, 0}; // 设置光标位
    SetConsoleCursorPosition(hStdout, newCursorPosition_1); // 移动光标
    GameBoard();
    // 初始蛇
//    COORD newCursorPosition_2 = {1, 1}; // 设置光标位
//    SetConsoleCursorPosition(hStdout, newCursorPosition_2); // 移动光标
//    printf("@");
    Board_Write(1, 1, "@");
    Board[1][1] = '@';
    struct Snack{
        int length; // 蛇的长度
        int body_direction[Board_Length*Board_Height]; // 蛇身的方向
        int tail_x;
        int tail_y;
        int head_direction;
    };
    // 初始化蛇
    struct Snack snack;
    snack.length = 1;
    snack.tail_x = 1;
    snack.tail_y = 1;
    snack.head_direction = my_RIGHT;
    snack.body_direction[0] = snack.head_direction;
    // 初始化果实
    struct Fruit{
        int X;
        int Y;
    };
    struct Fruit fruit;
    fruit.X = 10;
    fruit.Y = 10;

    // 游戏初始化
    int Key_Position = 0;
    while(1){
        // 判断按键
        if (GetAsyncKeyState('W') & 0x8000) {
            Key_Position = my_UP;
        }
        else if (GetAsyncKeyState('A') & 0x8000) {
            Key_Position = my_LEFT;
        }
        else if (GetAsyncKeyState('S') & 0x8000) {
            Key_Position = my_DOWN;
        }
        else if (GetAsyncKeyState('D') & 0x8000) {
            Key_Position = my_RIGHT;
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) {
            Key_Position = my_UP;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            Key_Position = my_DOWN;
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            Key_Position = my_LEFT;
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            Key_Position = my_RIGHT;
        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // ESC
            printf("Game over!\n");
            break; // 退出循环
        }
        else{
            Key_Position = 0;
        }
        // 如果方向有变化 --> 更新
        if (Key_Position){
            snack.head_direction = Key_Position;
        }
        // 根据按键移动方向
//        SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition); //恢复光标位置
        int Cursor_X=0, Cursor_Y=0;
        if(snack.head_direction == my_UP){
            Cursor_X = -1, Cursor_Y = -1;
        }
        else if(snack.head_direction == my_DOWN){
            Cursor_X = -1, Cursor_Y = 1;
        }
        else if(snack.head_direction == my_LEFT){
            Cursor_X = -2, Cursor_Y = 0;
        }
        else if(snack.head_direction == my_RIGHT){
            Cursor_X = 0, Cursor_Y = 0;
        }
        else{
            Cursor_X = 0, Cursor_Y = 0;
        }
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo_1;
        GetConsoleScreenBufferInfo(hStdout, &csbiInfo_1); // 获取当前光标位置
        // 移动蛇头
        if(csbiInfo_1.dwCursorPosition.X+Cursor_X <= 0 || csbiInfo_1.dwCursorPosition.Y+Cursor_Y <= 0 || csbiInfo_1.dwCursorPosition.X+Cursor_X >= Board_Length || csbiInfo_1.dwCursorPosition.Y+Cursor_Y >= Board_Height){
            break; // 过界
        }
        COORD newCursorPosition_3 = {csbiInfo_1.dwCursorPosition.X+Cursor_X, csbiInfo_1.dwCursorPosition.Y+Cursor_Y}; // 设置光标位
        SetConsoleCursorPosition(hStdout, newCursorPosition_3); // 移动光标
        printf("@");
        // 更新蛇身方向
        for(int i=0; i<snack.length-1; i++){
            snack.body_direction[i] = snack.body_direction[i+1];
        }
        // 更新蛇头方向
        snack.body_direction[snack.length-1] = snack.head_direction;
        // 如果吃到果实
        if(Board[csbiInfo_1.dwCursorPosition.Y+Cursor_Y][csbiInfo_1.dwCursorPosition.X+Cursor_X] == '$'){
            CONSOLE_SCREEN_BUFFER_INFO csbiInfo_4;
            GetConsoleScreenBufferInfo(hStdout, &csbiInfo_4); // 获取当前光标位置
            COORD newCursorPosition_6 = {csbiInfo_4.dwCursorPosition.X+Cursor_X, csbiInfo_4.dwCursorPosition.Y+Cursor_Y}; // 设置光标位
            SetConsoleCursorPosition(hStdout, newCursorPosition_6); // 移动光标
            printf("@");
            snack.length += 1;
            snack.body_direction[snack.length-1] = snack.head_direction; // 更新蛇头方向
            Board[csbiInfo_4.dwCursorPosition.Y+Cursor_Y][csbiInfo_4.dwCursorPosition.X+Cursor_X] = '@';
//            Sleep(1000);
        }
        Board[csbiInfo_1.dwCursorPosition.Y+Cursor_Y][csbiInfo_1.dwCursorPosition.X+Cursor_X] = '@';

        // 移动蛇尾
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo_2;
        GetConsoleScreenBufferInfo(hStdout, &csbiInfo_2); // 获取当前光标位置
        COORD newCursorPosition_4 = {snack.tail_x, snack.tail_y}; // 设置光标位
        SetConsoleCursorPosition(hStdout, newCursorPosition_4); // 移动光标
        printf(" ");
        Board[snack.tail_y][snack.tail_x] = ' ';
        SetConsoleCursorPosition(hStdout, csbiInfo_2.dwCursorPosition); //恢复光标位置
        if (snack.body_direction[0] == my_DOWN){
            snack.tail_y += 1;
        }
        else if(snack.body_direction[0] == my_UP){
            snack.tail_y -= 1;
        }
        else if(snack.body_direction[0] == my_RIGHT){
            snack.tail_x += 1;
        }
        else if(snack.body_direction[0] == my_LEFT){
            snack.tail_x -= 1;
        }

        // 随机果实
        if (Board[fruit.Y][fruit.X] != '$'){ //果实被吃掉了
            while(1){
                // int randomNumber = rand() % (max - min + 1) + min;
                int random_X = rand() % ((Board_Length-2) - 1 + 1) + 1;
                int random_Y = rand() % ((Board_Height-2) - 1 + 1) + 1;
                if(Board[random_Y][random_X] != '@'){
                    fruit.X = random_X;
                    fruit.Y = random_Y;
                    CONSOLE_SCREEN_BUFFER_INFO csbiInfo_3;
                    GetConsoleScreenBufferInfo(hStdout, &csbiInfo_3); // 获取当前光标位置
                    COORD newCursorPosition_5 = {random_X, random_Y}; // 设置光标位
                    SetConsoleCursorPosition(hStdout, newCursorPosition_5); // 移动光标
                    printf("$");
                    Board[fruit.Y][fruit.X] = '$';
                    SetConsoleCursorPosition(hStdout, csbiInfo_2.dwCursorPosition); //恢复光标位置
                    break;
                }
            }
        }
        Sleep(100);
    }
    GameOver();
    return 0;
}