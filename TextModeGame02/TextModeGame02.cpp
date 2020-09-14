// textModeGame_01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <conio.h>

void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
    gotoxy(x, y);
    setcolor(2, 4);
    std::cout << ("<=o=>");
}

void erase_ship(int x, int y)
{
    gotoxy(x, y);
    setcolor(0, 0);
    std::cout << ("     ");
}

//void horizontal_move_ship(int x, int y) {
//    char ch ='\0', isDirection = 's';
//    do {
//        if (_kbhit()) {
//            ch = _getch();
//            if (ch == 'a') {
//                isDirection = ch;
//                ch = '\0';
//            }else if (ch == 'd') {
//                isDirection = ch;
//                ch = '\0';
//            }
//            if (isDirection == 'a') {
//                erase_ship(x, y);
//                draw_ship(--x, y);
//            }
//            if (isDirection == 'd') {
//                erase_ship(x, y);
//                draw_ship(++x, y);
//            }
//            Sleep(100);
//            fflush(stdin);
//        }
//        Sleep(100);
//    } while (isDirection != 's');
//}

void beam_ship(int x, int y)
{
    while (y+1 > 0) {
        gotoxy(x, y);
        std::cout << "|";
        Sleep(50);
        gotoxy(x, y);
        setcolor(0, 0);
        std::cout << (" ");
        setcolor(2, 4);
        y--;
    }
}

void burst_beam(int x,int y,int bullet) {
    int position[100],b=y;
    for (int i = 0; i < bullet; i++)
    {
        position[i] = b;
        b += 2;
    }
    while (position[bullet-1]+1>0)
    {
        for (int i = 0; i < bullet; i++)
        {
            if (position[i]+1>0&&position[i]<=y)
            {
                gotoxy(x, position[i]);
                std::cout << "|";
                /*
                gotoxy(x, position[i]);
                setcolor(0, 0);
                std::cout << (" ");
                setcolor(2, 4);
                */
            }
        }
        Sleep(50);
        for (int i = 0; i < bullet; i++)
        {
            if (position[i] + 1 > 0 && position[i] <= y)
            {
                /*
                gotoxy(x, position[i]);
                std::cout << "|";
                Sleep(100);
                */
                gotoxy(x, position[i]);
                setcolor(0, 0);
                std::cout << (" ");
                setcolor(2, 4);
            }
        }
        for (int i = 0; i < bullet; i++)
        {
            position[i] -= 1;
        }
    }/**/
}

void obj_star(int x, int y)
{
    setcolor(14, 14);
    gotoxy(x, y);
    std::cout << " ";
    setcolor(2, 4);
}

int main()
{
    setcursor(0);
    char ch = ' ';
    int x = 38, y = 20;
    setcolor(2,4);
    draw_ship(x, y);
    /*obj_star(15, 7);
    obj_star(20, 17);
    obj_star(41, 2);
    obj_star(33, 21);
    obj_star(48, 5);
    obj_star(9, 19);*/
    do {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'a') {
                 do {
                    erase_ship(x, y);
                    draw_ship(--x, y);
                    Sleep(100);
                    if (_kbhit()) {
                        ch = _getch();
                    }
                 } while (x > 0 && ch != 's');
                 ch = '\0';
            }
            if (ch == 'd') {
                 do {
                    erase_ship(x, y);
                    draw_ship(++x, y);
                    Sleep(100);
                    if (_kbhit()) {
                        ch = _getch();
                    }
                 } while (x < 75 && ch != 's');
                 ch = '\0';
            }
            if (ch == 'w') {
                if (y > 0) {
                    erase_ship(x, y);
                    draw_ship(x, --y);
                }
            }
            if (ch == 's') {
                if (y < 25) {
                    erase_ship(x, y);
                    draw_ship(x, ++y);
                }
            }
            if (ch == ' ') {
                if (y < 25) {
                    burst_beam(x+2, y-1,5);
                }
            }
            fflush(stdin);
        }
        Sleep(100);
    } while (ch != 'x');


    return 0;
}