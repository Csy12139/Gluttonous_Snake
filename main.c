//
// Created by cissy on 2024/10/17.
//
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
# define Board_Length 100
# define Board_Height 20
# define my_UP 2
# define my_DOWN 3
# define my_LEFT 4
# define my_RIGHT 5
char Board[Board_Height][Board_Length];
HANDLE hStdout;
struct Snack{ // 蛇
    int length; // 蛇的长度
    int body_direction[Board_Length*Board_Height]; // 蛇身的方向
    int tail_x; // 蛇尾x坐标
    int tail_y; // 蛇尾y坐标
    int head_direction; // 蛇头方向
};
struct Snack snack;
struct Fruit{ // 果实
    int X;
    int Y;
};
struct Fruit fruit;
struct Cursor{ // 光标
    int X;
    int Y;
};
struct Cursor cursor;
// 隐藏光标
void HideCursor(){
    printf("\033[?25l");
    fflush(stdout);
}
// 显示光标
void show_cursor() {
    printf("\033[?25h");
    fflush(stdout);
}
// 游戏界面
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
CONSOLE_SCREEN_BUFFER_INFO Board_Write(HANDLE hStdout, int cursor_x, int cursor_y, const char *content){
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo); // 获取当前光标位置
    COORD newCursorPosition = {cursor_x, cursor_y}; // 设置光标位置
    SetConsoleCursorPosition(hStdout, newCursorPosition); // 移动光标
    printf("%s", content);
    fflush(stdout);
//    SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition); //恢复光标位置
    return csbiInfo;
}
// 游戏开始
void GameBegin(){
    HideCursor(); // 隐藏光标
    GameBoard();
    Board_Write(hStdout, Board_Length/3, Board_Height/3, "***** Gluttonous Snake *****\n");
    Board_Write(hStdout, Board_Length/3, Board_Height/3+2, "Game Begin: Press 'SPACEBAR'.\n");
}
// 游戏结束
void GameOver(){
    GameBoard();
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo = Board_Write(hStdout, Board_Length/3, Board_Height/3+2, "~~~~~ Game Over! ~~~~~\n");
    SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition); //恢复光标位置
    show_cursor(); // 显示光标
}
// 检查按键状态
int CheckKeyStatus(){
    int Key_Position = 0;
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
    else{
        Key_Position = 0;
    }
    return Key_Position;
}
// 游戏准备开始阶段
void GameReadyStart(){
    srand(time(NULL)); // 设置种子
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备的句柄
    GameBegin(); // 游戏开始界面
    // 等待用户触发SPACEBAR 开始游戏
    while(1){
        short s = GetAsyncKeyState(0x20 ); // SPACEBAR
        if((s & 0x8000)){
            break;
        }
    }
    GameBoard(); // 清屏
    // 初始化蛇
    Board_Write(hStdout, 1, 1, "@");
    Board[1][1] = '@';
    snack.length = 1;
    snack.tail_x = 1;
    snack.tail_y = 1;
    snack.head_direction = my_RIGHT;
    snack.body_direction[0] = snack.head_direction;
    // 初始化果实
    fruit.X = 10;
    fruit.Y = 10;
}
// 获取用户动作
void GetUserAction(){
//    struct Cursor cursor;
    // 判断按键
    int Key_Position = CheckKeyStatus(); // 检查按键状态
    // 如果方向有变化 --> 更新
    if (Key_Position){
        snack.head_direction = Key_Position;
    }
    // 根据按键移动方向
//    cursor.X=0, cursor.Y=0;
    if(snack.head_direction == my_UP){
        cursor.X = -1, cursor.Y = -1;
    }
    else if(snack.head_direction == my_DOWN){
        cursor.X = -1, cursor.Y = 1;
    }
    else if(snack.head_direction == my_LEFT){
        cursor.X = -2, cursor.Y = 0;
    }
    else if(snack.head_direction == my_RIGHT){
        cursor.X = 0, cursor.Y = 0;
    }
    else{
        cursor.X = 0, cursor.Y = 0;
    }
}
// 控制蛇的移动
CONSOLE_SCREEN_BUFFER_INFO SnackMove(){
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo_1;
    GetConsoleScreenBufferInfo(hStdout, &csbiInfo_1); // 获取当前光标位置
    // 移动蛇头
    if(csbiInfo_1.dwCursorPosition.X+cursor.X <= 0 || csbiInfo_1.dwCursorPosition.Y+cursor.Y <= 0 || csbiInfo_1.dwCursorPosition.X+cursor.X >= Board_Length - 1 || csbiInfo_1.dwCursorPosition.Y+cursor.Y >= Board_Height - 1){
        // break; // 过界
        GameOver();
        while(1){};
    }
    Board_Write(hStdout, csbiInfo_1.dwCursorPosition.X+cursor.X, csbiInfo_1.dwCursorPosition.Y+cursor.Y, "@");

    // 更新蛇身方向
    for(int i=0; i<snack.length-1; i++){
        snack.body_direction[i] = snack.body_direction[i+1];
    }
    // 更新蛇头方向
    snack.body_direction[snack.length-1] = snack.head_direction;
    // 如果吃到果实
    if(Board[csbiInfo_1.dwCursorPosition.Y+cursor.Y][csbiInfo_1.dwCursorPosition.X+cursor.X] == '$'){

        CONSOLE_SCREEN_BUFFER_INFO csbiInfo_4;
        GetConsoleScreenBufferInfo(hStdout, &csbiInfo_4); // 获取当前光标位置
        Board_Write(hStdout, csbiInfo_4.dwCursorPosition.X+cursor.X, csbiInfo_4.dwCursorPosition.Y+cursor.Y, "@");

        snack.length += 1;
        snack.body_direction[snack.length-1] = snack.head_direction; // 更新蛇头方向
        Board[csbiInfo_4.dwCursorPosition.Y+cursor.Y][csbiInfo_4.dwCursorPosition.X+cursor.X] = '@';
    }
    Board[csbiInfo_1.dwCursorPosition.Y+cursor.Y][csbiInfo_1.dwCursorPosition.X+cursor.X] = '@';

    // 移动蛇尾
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo_2 = Board_Write(hStdout, snack.tail_x, snack.tail_y, " ");
    SetConsoleCursorPosition(hStdout, csbiInfo_2.dwCursorPosition); //恢复光标位置
    Board[snack.tail_y][snack.tail_x] = ' ';
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

    return csbiInfo_2;
}
// 随机生成果实
void GenerateFruit(CONSOLE_SCREEN_BUFFER_INFO csbiInfo){
    if (Board[fruit.Y][fruit.X] != '$'){ //果实被吃掉了
        while(1){
            // int randomNumber = rand() % (max - min + 1) + min;
            int random_X = rand() % ((Board_Length-2) - 1 + 1) + 1;
            int random_Y = rand() % ((Board_Height-2) - 1 + 1) + 1;
            if(Board[random_Y][random_X] != '@'){
                fruit.X = random_X;
                fruit.Y = random_Y;
                Board_Write(hStdout, random_X, random_Y, "$");
                Board[fruit.Y][fruit.X] = '$';
                SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition); //恢复光标位置
                break;
            }
        }
    }
}
int main() {
    GameReadyStart(); // 游戏准备开始阶段
    while(1){
        // 获取用户动作
        GetUserAction();
        // 控制蛇的移动
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo_2 = SnackMove();
        // 随机生成果实
        GenerateFruit(csbiInfo_2);

        Sleep(100);
    }
    return 0;
}