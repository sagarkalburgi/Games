#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>`
#include <Windows.h>

using namespace std;
bool gameOver;
const int width = 40;	// screen width
const int height = 20;	// screen height
int x, y, fruitX, fruitY, score;	// x, y positions of the snake head, x, y positions of the fruit
int blockX, blockY; // x, y positions of the block
int tailX[1000], tailY[1000];	// store the tail x,y positions
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};	// Directions
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    blockX = rand() % width;
    blockY = rand() % height;
	score = 0;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (j == 0)
                cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "X";
			else if (i == blockY && j == blockX)
				cout << "B";
			else{
				bool print = false;
				for (int k = 0; k < nTail; k++){
					if (tailX[k] == j && tailY[k] == i){
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':	// press 'a' to move left
			if (dir == RIGHT) break;
			dir = LEFT;
			break;
		case 'd':	// press 'd' to move right
			if (dir == LEFT) break;
			dir = RIGHT;
			break;
		case 'w':	// press 'w' to move up
			if (dir == DOWN) break;
			dir = UP;
			break;
		case 's':	// press 's' to move down
			if (dir == UP) break;
			dir = DOWN;
			break;
		case 'p':	// press 'p' to move pause
			dir = STOP;
			break;
		case 'x':	// press 'x' to exit the game
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int preX = tailX[0];
	int preY = tailY[0];
	int pre2X, pre2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++){	// follow the head
		pre2X = tailX[i];
		pre2Y = tailY[i];
		tailX[i] = preX;
		tailY[i] = preY;
		preX = pre2X;
		preY = pre2Y;
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
	// Uncomment if you want the game to end if you hit the wall
	//if (x > width || x < 0 || y > height || y < 0)
		//gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;	// pass from horizontal walls
	if (y >= height) y = 0; else if (y < 0) y = height - 1;	// pass from vertical walls
	for (int i = 0; i < nTail; i++){	// game over it you head your tail
		if (tailX[i] == x && tailY[i] == y){
			cout << 'You head yourself!' << endl;
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY){	// increase tail if you eat a fruit
		score += 1;
		fruitX = rand() % width;	// new x position of the fruit
		fruitY = rand() % height;	// new y position of the fruit
		blockX = rand() % width;	// new x position of the block
		blockY = rand() % height;	// new y position of the block
		nTail++;
	}
	if (x == blockX && y == blockY){	// game end if you hit a block
		cout << "You hit a block!" << endl;
		gameOver = true;
	}
}

int main()
{
	srand((unsigned int)time(NULL));
    Setup();
    int ip;
    cout << "1. Start Game" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter you option: ";
    cin  >> ip;
    while(!gameOver && ip==1)
    {
        Draw();
        Input();
        Logic();
		//Sleep(1);
        Sleep(max(100-score*5, 1));
    }
    cout << "Game over!" << endl;
    return 0;
}
