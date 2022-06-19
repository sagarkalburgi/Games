#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <Windows.h>

using namespace std;
bool gameOver;
const int width = 9;	// screen width
const int height = 22;	// screen height
int x, y, x1, x2, x3, x4, x5, y1, y2, y3, y4, y5, score;	// x, y positions of the snake head, x, y positions of the fruit
int blockX1, blockY1, blockX2, blockY2, blockX3, blockY3, blockX4, blockY4, blockX5, blockY5, blockX6, blockY6; // x, y positions of the block
int xIdx[] = {1, 4, 7};
int blockN;
int tik;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};	// Directions
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    x1 = x;
    x2 = x+1;
    x3 = x-1;
    x4 = x+1;
    x5 = x-1;
    y = height - 2;
	y1 = y-2;
    y2 = y-1;
    y3 = y-1;
    y4 = y+1;
    y5 = y+1;
    int temp = rand() % 3;
    blockX1 = (xIdx[temp]);
    blockY1 = -2;
    blockX2 = -10;
    blockY2 = -10;
    blockX3 = -10;
    blockY3 = -10;
    blockX4 = -10;
    blockY4 = -10;
    blockX5 = -10;
    blockY5 = -10;
	blockX6 = -10;
    blockY6 = -10;
	blockN = 1;
	score = 0;
	tik = 0;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width+2; i++)
        cout << "$";
    cout << endl;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (j == 0)
                cout << "$";
			if (i == y && j == x)
				cout << "#";
			else if ((i == blockY1 && j == blockX1) || (i == blockY1-1 && j == blockX1-1) || (i == blockY1+1 && j == blockX1+1) ||
					(i == blockY1+1 && j == blockX1-1) || (i == blockY1-1 && j == blockX1+1) || (i == blockY1-2 && j == blockX1) ||
					(i == blockY2 && j == blockX2) || (i == blockY2-1 && j == blockX2-1) || (i == blockY2+1 && j == blockX2+1) ||
					(i == blockY2+1 && j == blockX2-1) || (i == blockY2-1 && j == blockX2+1) || (i == blockY2-2 && j == blockX2) ||
					(i == blockY3 && j == blockX3) || (i == blockY3-1 && j == blockX3-1) || (i == blockY3+1 && j == blockX3+1) ||
					(i == blockY3+1 && j == blockX3-1) || (i == blockY3-1 && j == blockX3+1) || (i == blockY3-2 && j == blockX3) ||
					(i == blockY4 && j == blockX4) || (i == blockY4-1 && j == blockX4-1) || (i == blockY4+1 && j == blockX4+1) ||
					(i == blockY4+1 && j == blockX4-1) || (i == blockY4-1 && j == blockX4+1) || (i == blockY4-2 && j == blockX4) ||
					(i == blockY5 && j == blockX5) || (i == blockY5-1 && j == blockX5-1) || (i == blockY5+1 && j == blockX5+1) ||
					(i == blockY5+1 && j == blockX5-1) || (i == blockY5-1 && j == blockX5+1) || (i == blockY5-2 && j == blockX5) ||
					(i == blockY6 && j == blockX6) || (i == blockY6-1 && j == blockX6-1) || (i == blockY6+1 && j == blockX6+1) ||
					(i == blockY6+1 && j == blockX6-1) || (i == blockY6-1 && j == blockX6+1) || (i == blockY6-2 && j == blockX6)){
				cout << "#";
			}

			else{
				bool print = false;
					if (x1 == j && y1 == i){
						cout << "#";
						print = true;
					}
					else if (x2 == j && y2 == i){
						cout << "#";
						print = true;
					}
					else if (x3 == j && y3 == i){
						cout << "#";
						print = true;
					}
					else if (x4 == j && y4 == i){
						cout << "#";
						print = true;
					}
					else if (x5 == j && y5 == i){
						cout << "#";
						print = true;
					}

				if (!print)
					cout << " ";
			}

            if (j == width - 1)
                cout << "$";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "$";
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
			dir = LEFT;
			break;
		case 'd':	// press 'd' to move right
			dir = RIGHT;
			break;
		case 'w':	// press 'w' to move up
			dir = UP;
			break;
		case 's':	// press 's' to move down
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
	switch (dir)
	{
	case LEFT:
		x = x-3;
		x1 = x;
		x2 = x+1;
		x3 = x-1;
		x4 = x+1;
		x5 = x-1;
		dir = STOP;
		break;
	case RIGHT:
		x = x+3;
		x1 = x;
		x2 = x+1;
		x3 = x-1;
		x4 = x+1;
		x5 = x-1;
		dir = STOP;
		break;
	case UP:
		y--;
		y1 = y-2;
		y2 = y-1;
		y3 = y-1;
		y4 = y+1;
		y5 = y+1;
		dir = STOP;
		break;
	case DOWN:
		y++;
		y1 = y-2;
		y2 = y-1;
		y3 = y-1;
		y4 = y+1;
		y5 = y+1;
		dir = STOP;
		break;
	default:
		break;
	}

	if (x4 > width-1){
		x = width-2;
		x1 = x;
		x2 = x+1;
		x3 = x-1;
		x4 = x+1;
		x5 = x-1;
	}
	if (x3 < 1){
		x = 1;
		x1 = x;
		x2 = x+1;
		x3 = x-1;
		x4 = x+1;
		x5 = x-1;
	} ;
	if (y5 > height-1){
		y = height-2;
		y1 = y-2;
		y2 = y-1;
		y3 = y-1;
		y4 = y+1;
		y5 = y+1;
	}
	if (y1 < 1){
		y = 2;
		y1 = y-2;
		y2 = y-1;
		y3 = y-1;
		y4 = y+1;
		y5 = y+1;
	}

	if ((x2 == blockX1-1 && y2 == blockY1-1) || (x2 == blockX1-1 && y2 == blockY1+1) || (x2 == blockX1-1 && y2 == blockY1+1) || (x2 == blockX1+1 && y2 == blockY1+1) || (x2 == blockX1 && y2 == blockY1-2) ||
		(x3 == blockX1-1 && y3 == blockY1-1) || (x3 == blockX1-1 && y3 == blockY1+1) || (x3 == blockX1-1 && y3 == blockY1+1) || (x3 == blockX1+1 && y3 == blockY1+1) || (x2 == blockX1 && y3 == blockY1-2) ||
		(x2 == blockX1-1 && y4 == blockY1-1) || (x2 == blockX1-1 && y4 == blockY1+1) || (x2 == blockX1-1 && y4 == blockY1+1) || (x2 == blockX1+1 && y4 == blockY1+1) || (x2 == blockX1 && y4 == blockY1-2) ||
		(x2 == blockX1-1 && y5 == blockY1-1) || (x2 == blockX1-1 && y5 == blockY1+1) || (x2 == blockX1-1 && y5 == blockY1+1) || (x2 == blockX1+1 && y5 == blockY1+1) || (x2 == blockX1 && y5 == blockY1-2) ||
		(x2 == blockX1-1 && y1 == blockY1-1) || (x2 == blockX1-1 && y1 == blockY1+1) || (x2 == blockX1-1 && y1 == blockY1+1) || (x2 == blockX1+1 && y1 == blockY1+1) || (x2 == blockX1 && y1 == blockY1-2) ||

		(x2 == blockX2-1 && y2 == blockY2-1) || (x2 == blockX2-1 && y2 == blockY2+1) || (x2 == blockX2-1 && y2 == blockY2+1) || (x2 == blockX2+1 && y2 == blockY2+1) || (x2 == blockX2 && y2 == blockY2-2) ||
		(x3 == blockX2-1 && y3 == blockY2-1) || (x3 == blockX2-1 && y3 == blockY2+1) || (x3 == blockX2-1 && y3 == blockY2+1) || (x3 == blockX2+1 && y3 == blockY2+1) || (x2 == blockX2 && y3 == blockY2-2) ||
		(x2 == blockX2-1 && y4 == blockY2-1) || (x2 == blockX2-1 && y4 == blockY2+1) || (x2 == blockX2-1 && y4 == blockY2+1) || (x2 == blockX2+1 && y4 == blockY2+1) || (x2 == blockX2 && y4 == blockY2-2) ||
		(x2 == blockX2-1 && y5 == blockY2-1) || (x2 == blockX2-1 && y5 == blockY2+1) || (x2 == blockX2-1 && y5 == blockY2+1) || (x2 == blockX2+1 && y5 == blockY2+1) || (x2 == blockX2 && y5 == blockY2-2) ||
		(x2 == blockX2-1 && y1 == blockY2-1) || (x2 == blockX2-1 && y1 == blockY2+1) || (x2 == blockX2-1 && y1 == blockY2+1) || (x2 == blockX2+1 && y1 == blockY2+1) || (x2 == blockX2 && y1 == blockY2-2) ||

		(x2 == blockX3-1 && y2 == blockY3-1) || (x2 == blockX3-1 && y2 == blockY3+1) || (x2 == blockX3-1 && y2 == blockY3+1) || (x2 == blockX3+1 && y2 == blockY3+1) || (x2 == blockX3 && y2 == blockY3-2) ||
		(x3 == blockX3-1 && y3 == blockY3-1) || (x3 == blockX3-1 && y3 == blockY3+1) || (x3 == blockX3-1 && y3 == blockY3+1) || (x3 == blockX3+1 && y3 == blockY3+1) || (x2 == blockX3 && y3 == blockY3-2) ||
		(x2 == blockX3-1 && y4 == blockY3-1) || (x2 == blockX3-1 && y4 == blockY3+1) || (x2 == blockX3-1 && y4 == blockY3+1) || (x2 == blockX3+1 && y4 == blockY3+1) || (x2 == blockX3 && y4 == blockY3-2) ||
		(x2 == blockX3-1 && y5 == blockY3-1) || (x2 == blockX3-1 && y5 == blockY3+1) || (x2 == blockX3-1 && y5 == blockY3+1) || (x2 == blockX3+1 && y5 == blockY3+1) || (x2 == blockX3 && y5 == blockY3-2) ||
		(x2 == blockX3-1 && y1 == blockY3-1) || (x2 == blockX3-1 && y1 == blockY3+1) || (x2 == blockX3-1 && y1 == blockY3+1) || (x2 == blockX3+1 && y1 == blockY3+1) || (x2 == blockX3 && y1 == blockY3-2)){
		gameOver = true;
	}

	if ((x2 == blockX4-1 && y2 == blockY4-1) || (x2 == blockX4-1 && y2 == blockY4+1) || (x2 == blockX4-1 && y2 == blockY4+1) || (x2 == blockX4+1 && y2 == blockY4+1) || (x2 == blockX4 && y2 == blockY4-2) ||
		(x3 == blockX4-1 && y3 == blockY4-1) || (x3 == blockX4-1 && y3 == blockY4+1) || (x3 == blockX4-1 && y3 == blockY4+1) || (x3 == blockX4+1 && y3 == blockY4+1) || (x2 == blockX4 && y3 == blockY4-2) ||
		(x2 == blockX4-1 && y4 == blockY4-1) || (x2 == blockX4-1 && y4 == blockY4+1) || (x2 == blockX4-1 && y4 == blockY4+1) || (x2 == blockX4+1 && y4 == blockY4+1) || (x2 == blockX4 && y4 == blockY4-2) ||
		(x2 == blockX4-1 && y5 == blockY4-1) || (x2 == blockX4-1 && y5 == blockY4+1) || (x2 == blockX4-1 && y5 == blockY4+1) || (x2 == blockX4+1 && y5 == blockY4+1) || (x2 == blockX4 && y5 == blockY4-2) ||
		(x2 == blockX4-1 && y1 == blockY4-1) || (x2 == blockX4-1 && y1 == blockY4+1) || (x2 == blockX4-1 && y1 == blockY4+1) || (x2 == blockX4+1 && y1 == blockY4+1) || (x2 == blockX4 && y1 == blockY4-2) ||

		(x2 == blockX5-1 && y2 == blockY5-1) || (x2 == blockX5-1 && y2 == blockY5+1) || (x2 == blockX5-1 && y2 == blockY5+1) || (x2 == blockX5+1 && y2 == blockY5+1) || (x2 == blockX5 && y2 == blockY5-2) ||
		(x3 == blockX5-1 && y3 == blockY5-1) || (x3 == blockX5-1 && y3 == blockY5+1) || (x3 == blockX5-1 && y3 == blockY5+1) || (x3 == blockX5+1 && y3 == blockY5+1) || (x2 == blockX5 && y3 == blockY5-2) ||
		(x2 == blockX5-1 && y4 == blockY5-1) || (x2 == blockX5-1 && y4 == blockY5+1) || (x2 == blockX5-1 && y4 == blockY5+1) || (x2 == blockX5+1 && y4 == blockY5+1) || (x2 == blockX5 && y4 == blockY5-2) ||
		(x2 == blockX5-1 && y5 == blockY5-1) || (x2 == blockX5-1 && y5 == blockY5+1) || (x2 == blockX5-1 && y5 == blockY5+1) || (x2 == blockX5+1 && y5 == blockY5+1) || (x2 == blockX5 && y5 == blockY5-2) ||
		(x2 == blockX5-1 && y1 == blockY5-1) || (x2 == blockX5-1 && y1 == blockY5+1) || (x2 == blockX5-1 && y1 == blockY5+1) || (x2 == blockX5+1 && y1 == blockY5+1) || (x2 == blockX5 && y1 == blockY5-2) ||

		(x2 == blockX6-1 && y2 == blockY6-1) || (x2 == blockX6-1 && y2 == blockY6+1) || (x2 == blockX6-1 && y2 == blockY6+1) || (x2 == blockX6+1 && y2 == blockY6+1) || (x2 == blockX6 && y2 == blockY6-2) ||
		(x3 == blockX6-1 && y3 == blockY6-1) || (x3 == blockX6-1 && y3 == blockY6+1) || (x3 == blockX6-1 && y3 == blockY6+1) || (x3 == blockX6+1 && y3 == blockY6+1) || (x2 == blockX6 && y3 == blockY6-2) ||
		(x2 == blockX6-1 && y4 == blockY6-1) || (x2 == blockX6-1 && y4 == blockY6+1) || (x2 == blockX6-1 && y4 == blockY6+1) || (x2 == blockX6+1 && y4 == blockY6+1) || (x2 == blockX6 && y4 == blockY6-2) ||
		(x2 == blockX6-1 && y5 == blockY6-1) || (x2 == blockX6-1 && y5 == blockY6+1) || (x2 == blockX6-1 && y5 == blockY6+1) || (x2 == blockX6+1 && y5 == blockY6+1) || (x2 == blockX6 && y5 == blockY6-2) ||
		(x2 == blockX6-1 && y1 == blockY6-1) || (x2 == blockX6-1 && y1 == blockY6+1) || (x2 == blockX6-1 && y1 == blockY6+1) || (x2 == blockX6+1 && y1 == blockY6+1) || (x2 == blockX6 && y1 == blockY6-2)){
		gameOver = true;
	}

	if ((blockY1 == height && score <= 10) || (blockY1 == height && blockN == 1)){
		int temp = rand() % 3;
		blockX1 = (xIdx[temp]);
		blockY1 = -2;
		score++;
		blockN = (rand() % 2) + 1;
	}

	if ((blockY2 == height && score <= 10) || (blockY2 == height && blockN == 1)){
		int temp = rand() % 3;
		blockX2 = (xIdx[temp]);
		blockY2 = -2;
		score++;
		blockN = (rand() % 2) + 1;
	}

	if ((blockY3 == height && score <= 10) || (blockY3 == height && blockN == 1)){
		int temp = rand() % 3;
		blockX3 = (xIdx[temp]);
		blockY3 = -2;
		score++;
		blockN = (rand() % 2) + 1;
	}

	if ((blockY1 == 6 && score <= 10) || (blockY1 == 6 && blockN == 1)){
		int temp = rand() % 3;
		blockX2 = (xIdx[temp]);
		blockY2 = -2;
	}

	if ((blockY2 == 6 && score <= 10) || (blockY2 == 6 && blockN == 1)){
		int temp = rand() % 3;
		blockX3 = (xIdx[temp]);
		blockY3 = -2;
	}

	if ((blockY1 == height && score > 10) && (blockY1 == height && blockN == 2)){
		int temp = rand() % 3;
		int temp1 = rand() % 3;
		while(temp == temp1){
			temp1 = rand() % 3;
		}
		blockX1 = (xIdx[temp]);
		blockY1 = -2;
		blockX4 = (xIdx[temp1]);
		blockY4 = -2;
		score++;
		blockN = (rand() % 2) + 1;
	}

	if ((blockY2 == height && score > 10) && (blockY2 == height && blockN == 2)){
		int temp = rand() % 3;
		int temp1 = rand() % 3;
		while(temp == temp1){
			temp1 = rand() % 3;
		}
		blockX2 = (xIdx[temp]);
		blockY2 = -2;
		blockX5 = (xIdx[temp1]);
		blockY5 = -2;
		score++;
		blockN = (rand() % 2) + 1;
	}

	if ((blockY3 == height && score > 10) && (blockY3 == height && blockN == 2)){
		int temp = rand() % 3;
		int temp1 = rand() % 3;
		while(temp == temp1){
			temp1 = rand() % 3;
		}
		blockX3 = (xIdx[temp]);
		blockY3 = -2;
		blockX6 = (xIdx[temp1]);
		blockY6 = -2;
		score++;
		blockN = (rand() % 2) + 1;
	}

	if (blockY1 == 6 && blockN == 2 && score > 10){
		int temp = rand() % 3;
		int temp1 = rand() % 3;
		while(temp == temp1){
			temp1 = rand() % 3;
		}
		blockX2 = (xIdx[temp]);
		blockY2 = -2;
		blockX5 = (xIdx[temp1]);
		blockY5 = -2;
	}

	if (blockY2 == 6 && blockN == 2 && score > 10){
		int temp = rand() % 3;
		int temp1 = rand() % 3;
		while(temp == temp1){
			temp1 = rand() % 3;
		}
		blockX3 = (xIdx[temp]);
		blockY3 = -2;
		blockX6 = (xIdx[temp1]);
		blockY6 = -2;
	}

}

void MoveDown(){
	blockY1 += 1;
	blockY2 += 1;
	blockY3 += 1;
	blockY4 += 1;
	blockY5 += 1;
	blockY6 += 1;
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
    while(!gameOver)
    {
		Draw();
        Input();
        Logic();
        tik ++ ;
        if (score <= 10){
			if (tik % 2 == 0){
				MoveDown();
			}
        }
        else{
			MoveDown();
        }
        Sleep(min(score+5,20));
    }
    cout << "Game over!" << endl;
    return 0;
}
