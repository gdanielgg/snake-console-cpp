#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
using namespace std;
bool gameOver;
int x, y, fruitX, fruitY, score, tail=0,tailX[100],tailY[100];
const int height = 20;
const int width = 20;
enum direction { STOP = 0, UP,DOWN,LEFT,RIGHT };
direction dir;
void Setup()
{
    gameOver = 0;
    score = 0;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % 18+1;
    fruitY = rand() % 18+1;
    srand(time(NULL));
}
void Draw()
{
    system("cls");
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                if (i == y && j == x)
                    cout << "O";
                else if (i == fruitY && j == fruitX)
                    cout << "F";
                if (j == 0)
                    cout << "#";
                else if (i == 0)
                    cout << "#";
                else if (j == height - 1)
                    cout << "#";
                else if (i == width - 1)
                    cout << "#";
                else
                {
                    bool print=false;
                    for(int k=0;k<tail;k++)
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << "o";
                            print = true;
                        }
                    if (!print)
                        cout << " ";
                }
            }
        }
        cout << endl;
    }
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
                dir = LEFT;
                break;
        case 'd':
                dir = RIGHT;
                break;
        case 'w':
                dir = UP;
                break;
        case 's':
                dir = DOWN;
                break;
        case 'x':
                gameOver = true;
                break;
        default:
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < tail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x<=0 || x>=width-1 || y<=0 || y>=width-1)
        gameOver = true;
    for (int i = 0; i < tail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    if (x == fruitX && y == fruitY)
    {
        tail++;
        fruitX = rand() % 18+1;
        fruitY = rand() % 18+1;
        score += 10;
    }
    
    
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(50);
    }
    return 0;
}
