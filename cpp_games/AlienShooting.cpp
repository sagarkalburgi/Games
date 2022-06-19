#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <Windows.h>

using namespace std;
bool gameOver;
const int width = 20;	// screen width
const int height = 20;	// screen height
int x, y, x1, x2, x3, x4, x5, y1, y2, y3, y4, y5;
int bx[20];
int by[20];
int by1[20];
int by2[20];
int by3[20];
int by4[20];
int by5[20];
int by6[20];
int by7[20];
int by8[20];
int temp1 = 0, temp2 = 0;
bool cond[20];
bool cond1[20];
bool cond2[20];
bool cond3[20];
bool cond4[20];
bool cond5[20];
bool cond6[20];
bool cond7[20];
bool cond8[20];
int condT = 0;
bool gun2;
int hitCount;
int Level = 0;
bool byCond, byCond1, byCond2, byCond3, byCond4, byCond5, byCond6, byCond7, byCond8;
bool gunCond, gunCond1;
bool condGunHit[20];
bool condGunHit1[20];
bool condGunHit2[20];
bool condGunHit3[20];
bool condGunHit4[20];
bool condGunHit5[20];
bool condGunHit6[20];
bool condGunHit7[20];
bool condGunHit8[20];
int gunX, gunY, gun1X, gun1Y;
int score = 0;
enum eDirection {STOP = 0, LEFT, RIGHT, SHOOT, NOSHOOT};	// Directions
eDirection dir;

void Setup()
{
    gameOver = false;
    gunCond = false;
    gunCond1 = false;
    dir = STOP;
    hitCount = 0;
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
    gun1Y = y-2;
    gunY = y-2;
    byCond = false;
    byCond1 = false;
    byCond2 = false;
    byCond3 = false;
    byCond4 = false;
    byCond5 = false;
    byCond6 = false;
    byCond7 = false;
    byCond8 = false;
    gun2 = false;

	for (int i=0; i<width;i++){
		by[i] = 0;
		bx[i] = i;
		by1[i] = -10;
		by2[i] = -10;
		by3[i] = -10;
		by4[i] = -10;
		by5[i] = -10;
		by6[i] = -10;
		by7[i] = -10;
		by8[i] = -10;
		cond[i] = false;
		cond1[i] = false;
		cond2[i] = false;
		cond3[i] = false;
		cond4[i] = false;
		cond5[i] = false;
		cond6[i] = false;
		cond7[i] = false;
		cond8[i] = false;
		condGunHit[i] = true;
		condGunHit1[i] = true;
		condGunHit2[i] = true;
		condGunHit3[i] = true;
		condGunHit4[i] = true;
		condGunHit5[i] = true;
		condGunHit6[i] = true;
		condGunHit7[i] = true;
		condGunHit8[i] = true;
	}
}

void CheckCondition(){
	for (int z=1;z<width-1;z++){
		if (temp2==bx[z] && temp1==by[z] && condGunHit[z]){
				cond[z] = true;
		}
		else cond[z] = false;
		if (temp2==bx[z] && temp1==by1[z] && condGunHit1[z]){
			cond1[z] = true;
		}
		else cond1[z] = false;
		if (temp2==bx[z] && temp1==by2[z] && condGunHit2[z]){
			cond2[z] = true;
		}
		else cond2[z] = false;
		if (temp2==bx[z] && temp1==by3[z] && condGunHit3[z]){
			cond3[z] = true;
		}
		else cond3[z] = false;
		if (temp2==bx[z] && temp1==by4[z] && condGunHit4[z]){
			cond4[z] = true;
		}
		else cond4[z] = false;
		if (temp2==bx[z] && temp1==by5[z] && condGunHit5[z]){
			cond5[z] = true;
		}
		else cond5[z] = false;
		if (temp2==bx[z] && temp1==by6[z] && condGunHit6[z]){
			cond6[z] = true;
		}
		else cond6[z] = false;
		if (temp2==bx[z] && temp1==by7[z] && condGunHit7[z]){
			cond7[z] = true;
		}
		else cond7[z] = false;
		if (temp2==bx[z] && temp1==by8[z] && condGunHit8[z]){
			cond8[z] = true;
		}
		else cond8[z] = false;
	}
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width+2; i++)
        cout << "$";
    cout << endl;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
			temp1 = i;
			temp2 = j;
			CheckCondition();
            if (j == 0)
                cout << "$";
			if (i == y && j == x)
				cout << "#";

			else if (cond[1]) cout << "0";
			else if (cond[2]) cout << "0";
			else if (cond[3]) cout << "0";
			else if (cond[4]) cout << "0";
			else if (cond[5]) cout << "0";
			else if (cond[6]) cout << "0";
			else if (cond[7]) cout << "0";
			else if (cond[8]) cout << "0";
			else if (cond[9]) cout << "0";
			else if (cond[10]) cout << "0";
			else if (cond[11]) cout << "0";
			else if (cond[12]) cout << "0";
			else if (cond[13]) cout << "0";
			else if (cond[14]) cout << "0";
			else if (cond[15]) cout << "0";
			else if (cond[16]) cout << "0";
			else if (cond[17]) cout << "0";
			else if (cond[18]) cout << "0";

			else if (cond1[1]) cout << "0";
			else if (cond1[2]) cout << "0";
			else if (cond1[3]) cout << "0";
			else if (cond1[4]) cout << "0";
			else if (cond1[5]) cout << "0";
			else if (cond1[6]) cout << "0";
			else if (cond1[7]) cout << "0";
			else if (cond1[8]) cout << "0";
			else if (cond1[9]) cout << "0";
			else if (cond1[10]) cout << "0";
			else if (cond1[11]) cout << "0";
			else if (cond1[12]) cout << "0";
			else if (cond1[13]) cout << "0";
			else if (cond1[14]) cout << "0";
			else if (cond1[15]) cout << "0";
			else if (cond1[16]) cout << "0";
			else if (cond1[17]) cout << "0";
			else if (cond1[18]) cout << "0";

			else if (cond2[1]) cout << "0";
			else if (cond2[2]) cout << "0";
			else if (cond2[3]) cout << "0";
			else if (cond2[4]) cout << "0";
			else if (cond2[5]) cout << "0";
			else if (cond2[6]) cout << "0";
			else if (cond2[7]) cout << "0";
			else if (cond2[8]) cout << "0";
			else if (cond2[9]) cout << "0";
			else if (cond2[10]) cout << "0";
			else if (cond2[11]) cout << "0";
			else if (cond2[12]) cout << "0";
			else if (cond2[13]) cout << "0";
			else if (cond2[14]) cout << "0";
			else if (cond2[15]) cout << "0";
			else if (cond2[16]) cout << "0";
			else if (cond2[17]) cout << "0";
			else if (cond2[18]) cout << "0";

			else if (cond3[1]) cout << "0";
			else if (cond3[2]) cout << "0";
			else if (cond3[3]) cout << "0";
			else if (cond3[4]) cout << "0";
			else if (cond3[5]) cout << "0";
			else if (cond3[6]) cout << "0";
			else if (cond3[7]) cout << "0";
			else if (cond3[8]) cout << "0";
			else if (cond3[9]) cout << "0";
			else if (cond3[10]) cout << "0";
			else if (cond3[11]) cout << "0";
			else if (cond3[12]) cout << "0";
			else if (cond3[13]) cout << "0";
			else if (cond3[14]) cout << "0";
			else if (cond3[15]) cout << "0";
			else if (cond3[16]) cout << "0";
			else if (cond3[17]) cout << "0";
			else if (cond3[18]) cout << "0";

			else if (cond4[1]) cout << "0";
			else if (cond4[2]) cout << "0";
			else if (cond4[3]) cout << "0";
			else if (cond4[4]) cout << "0";
			else if (cond4[5]) cout << "0";
			else if (cond4[6]) cout << "0";
			else if (cond4[7]) cout << "0";
			else if (cond4[8]) cout << "0";
			else if (cond4[9]) cout << "0";
			else if (cond4[10]) cout << "0";
			else if (cond4[11]) cout << "0";
			else if (cond4[12]) cout << "0";
			else if (cond4[13]) cout << "0";
			else if (cond4[14]) cout << "0";
			else if (cond4[15]) cout << "0";
			else if (cond4[16]) cout << "0";
			else if (cond4[17]) cout << "0";
			else if (cond4[18]) cout << "0";

			else if (cond5[1]) cout << "0";
			else if (cond5[2]) cout << "0";
			else if (cond5[3]) cout << "0";
			else if (cond5[4]) cout << "0";
			else if (cond5[5]) cout << "0";
			else if (cond5[6]) cout << "0";
			else if (cond5[7]) cout << "0";
			else if (cond5[8]) cout << "0";
			else if (cond5[9]) cout << "0";
			else if (cond5[10]) cout << "0";
			else if (cond5[11]) cout << "0";
			else if (cond5[12]) cout << "0";
			else if (cond5[13]) cout << "0";
			else if (cond5[14]) cout << "0";
			else if (cond5[15]) cout << "0";
			else if (cond5[16]) cout << "0";
			else if (cond5[17]) cout << "0";
			else if (cond5[18]) cout << "0";

			else if (cond6[1]) cout << "0";
			else if (cond6[2]) cout << "0";
			else if (cond6[3]) cout << "0";
			else if (cond6[4]) cout << "0";
			else if (cond6[5]) cout << "0";
			else if (cond6[6]) cout << "0";
			else if (cond6[7]) cout << "0";
			else if (cond6[8]) cout << "0";
			else if (cond6[9]) cout << "0";
			else if (cond6[10]) cout << "0";
			else if (cond6[11]) cout << "0";
			else if (cond6[12]) cout << "0";
			else if (cond6[13]) cout << "0";
			else if (cond6[14]) cout << "0";
			else if (cond6[15]) cout << "0";
			else if (cond6[16]) cout << "0";
			else if (cond6[17]) cout << "0";
			else if (cond6[18]) cout << "0";

			else if (cond7[1]) cout << "0";
			else if (cond7[2]) cout << "0";
			else if (cond7[3]) cout << "0";
			else if (cond7[4]) cout << "0";
			else if (cond7[5]) cout << "0";
			else if (cond7[6]) cout << "0";
			else if (cond7[7]) cout << "0";
			else if (cond7[8]) cout << "0";
			else if (cond7[9]) cout << "0";
			else if (cond7[10]) cout << "0";
			else if (cond7[11]) cout << "0";
			else if (cond7[12]) cout << "0";
			else if (cond7[13]) cout << "0";
			else if (cond7[14]) cout << "0";
			else if (cond7[15]) cout << "0";
			else if (cond7[16]) cout << "0";
			else if (cond7[17]) cout << "0";
			else if (cond7[18]) cout << "0";

			else if (cond8[1]) cout << "0";
			else if (cond8[2]) cout << "0";
			else if (cond8[3]) cout << "0";
			else if (cond8[4]) cout << "0";
			else if (cond8[5]) cout << "0";
			else if (cond8[6]) cout << "0";
			else if (cond8[7]) cout << "0";
			else if (cond8[8]) cout << "0";
			else if (cond8[9]) cout << "0";
			else if (cond8[10]) cout << "0";
			else if (cond8[11]) cout << "0";
			else if (cond8[12]) cout << "0";
			else if (cond8[13]) cout << "0";
			else if (cond8[14]) cout << "0";
			else if (cond8[15]) cout << "0";
			else if (cond8[16]) cout << "0";
			else if (cond8[17]) cout << "0";
			else if (cond8[18]) cout << "0";

			else if (gunCond && gunX == j && gunY == i){
				cout << '"';
			}

			else if (gunCond1 && gun1X == j && gun1Y == i){
				cout << '"';
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
    cout << "Level: " << Level << endl;
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
		case 'p':	// press 'p' to move pause
			dir = STOP;
			break;
		case 'k':	// press 'p' to move pause
			dir = SHOOT;
			break;
		case 'l':	// press 'p' to move pause
			dir = NOSHOOT;
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
		x--;
		x1 = x;
		x2 = x+1;
		x3 = x-1;
		x4 = x+1;
		x5 = x-1;
		dir = STOP;
		break;
	case RIGHT:
		x++;
		x1 = x;
		x2 = x+1;
		x3 = x-1;
		x4 = x+1;
		x5 = x-1;
		dir = STOP;
		break;
	case SHOOT:
		gunCond = true;
		gunCond1 = true;
		dir = STOP;
		break;
	case NOSHOOT:
		gunCond = false;
		gunCond1 = false;
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
	}

	if (gunCond){
		gunX = x;
		gunY--;
	}

	if (gunY <= 10) gun2 = true;

	if (gun2){
		gun1X = x;
		gun1Y--;
	}
	if (gunY == 0){
			gunY = y-2;
			gunX = x;
	}
	if (gun1Y == 0){
		gun1Y = y-2;
		gun1X = x;
		gun2 = false;
	}

	for (int i=0;i<width;i++){
		if (by[i] == y1 || by1[i] == y1 || by2[i] == y1 || by3[i] == y1 || by4[i] == y1 ||
			by5[i] == y1 || by6[i] == y1 || by7[i] == y1 || by8[i] == y1){
			gameOver = true;
		}
	}

	for (int i=1; i<width-1;i++){
		if (by[i] == gunY && bx[i] == gunX){
			gunY = y-2;
			gunX = x;
			score += 5;
			by[i] = -10;
			condGunHit[i] = false;
		}

		if (by[i] == gun1Y && bx[i] == gun1X){
			gun1Y = y-2;
			gun1X = x;
			score += 5;
			gun2 = false;
			by[i] = -10;
			condGunHit[i] = false;
		}

		if (by1[i] == gunY && bx[i] == gunX){
			gunY = y-2;
			gunX = x;
			score += 5;
			by1[i] = -10;
			condGunHit1[i] = false;
		}

		if (by1[i] == gun1Y && bx[i] == gun1X){
			gun1Y = y-2;
			gun1X = x;
			score += 5;
			gun2 = false;
			by1[i] = -10;
			condGunHit1[i] = false;
		}

		if (by2[i] == gunY && bx[i] == gunX){
			gunY = y-2;
			gunX = x;
			score += 5;
			by2[i] = -10;
			condGunHit2[i] = false;
		}

		if (by2[i] == gun1Y && bx[i] == gun1X){
			gun1Y = y-2;
			gun1X = x;
			score += 5;
			gun2 = false;
			by2[i] = -10;
			condGunHit2[i] = false;
		}

		if (by3[i] == gunY && bx[i] == gunX){
			gunY = y-2;
			gunX = x;
			score += 5;
			by3[i] = -10;
			condGunHit3[i] = false;
		}

		if (by3[i] == gun1Y && bx[i] == gun1X){
			gun1Y = y-2;
			gun1X = x;
			score += 5;
			gun2 = false;
			by3[i] = -10;
			condGunHit3[i] = false;
		}

		if (by4[i] == gunY && bx[i] == gunX){
			gunY = y-2;
			gunX = x;
			score += 5;
			by4[i] = -10;
			condGunHit4[i] = false;
		}

		if (by4[i] == gun1Y && bx[i] == gun1X){
			gun1Y = y-2;
			gun1X = x;
			score += 5;
			gun2 = false;
			by4[i] = -10;
			condGunHit4[i] = false;
		}

		if (by5[i] == gunY && bx[i] == gunX){
			gunY = y-2;
			gunX = x;
			score += 5;
			by5[i] = -10;
			condGunHit5[i] = false;
		}

		if (by5[i] == gun1Y && bx[i] == gun1X){
			gun1Y = y-2;
			gun1X = x;
			score += 5;
			gun2 = false;
			by5[i] = -10;
			condGunHit5[i] = false;
		}

		if (by6[i] == gunY && bx[i] == gunX){
			gunY = y-2;
			gunX = x;
			score += 5;
			by6[i] = -10;
			condGunHit6[i] = false;
		}

		if (by6[i] == gun1Y && bx[i] == gun1X){
			gun1Y = y-2;
			gun1X = x;
			score += 5;
			gun2 = false;
			by6[i] = -10;
			condGunHit6[i] = false;
		}

		if (by7[i] == gunY && bx[i] == gunX){
			gunY = y-2;
			gunX = x;
			score += 5;
			by7[i] = -10;
			condGunHit7[i] = false;
		}

		if (by7[i] == gun1Y && bx[i] == gun1X){
			gun1Y = y-2;
			gun1X = x;
			score += 5;
			gun2 = false;
			by7[i] = -10;
			condGunHit7[i] = false;
		}


		if (by8[i] == gunY && bx[i] == gunX){
			gunY = y-2;
			gunX = x;
			score += 5;
			by8[i] = -10;
			hitCount += 1;
			condGunHit8[i] = false;
		}

		if (by8[i] == gun1Y && bx[i] == gun1X){
			gun1Y = y-2;
			gun1X = x;
			score += 5;
			gun2 = false;
			by8[i] = -10;
			hitCount += 1;
			condGunHit8[i] = false;
		}
	}


}

void MoveObs(){
	for (int i=1; i<width-1;i++){
		if (condGunHit[i]) by[i] += 1;
	}

	for (int i=1;i<width-1;i++){
		if (by[i]>=2){
			byCond = true;
		}
		if (by1[i]>=1){
			byCond1 = true;
		}
		if (by2[i]>=1){
			byCond2 = true;
		}
		if (by3[i]>=1){
			byCond3 = true;
		}
		if (by4[i]>=1){
			byCond4 = true;
		}
		if (by5[i]>=1){
			byCond5 = true;
		}
		if (by6[i]>=1){
			byCond6 = true;
		}
		if (by7[i]>=1){
			byCond7 = true;
		}
		if (by8[i]>=1){
			byCond8 = true;
		}
	}

	for (int i=1;i<width-1;i++){
		bool test = false;
		if(byCond){
			for (int j=1;j<width-1;j++){
				if(by1[j] == -10) by1[j] = -1;
				if (condGunHit1[j]) by1[j] += 1;
			}
			test = true;
		}
		if (test) break;
		}

	for (int i=1;i<width-1;i++){
		bool test = false;
		if(byCond1){
			for (int j=1;j<width-1;j++){
				if(by2[j] == -10) by2[j] = -1;
				if (condGunHit2[j]) by2[j] += 1;
			}
			test = true;
		}
		if (test) break;
		}

	for (int i=1;i<width-1;i++){
		bool test = false;
		if(byCond2){
			for (int j=1;j<width-1;j++){
				if(by3[j] == -10) by3[j] = -1;
				if (condGunHit3[j]) by3[j] += 1;
			}
			test = true;
		}
		if (test) break;
		}

	for (int i=1;i<width-1;i++){
		bool test = false;
		if(byCond3){
			for (int j=1;j<width-1;j++){
				if(by4[j] == -10) by4[j] = -1;
				if (condGunHit4[j]) by4[j] += 1;
			}
			test = true;
		}
		if (test) break;
		}

	for (int i=1;i<width-1;i++){
		bool test = false;
		if(byCond4){
			for (int j=1;j<width-1;j++){
				if(by5[j] == -10) by5[j] = -1;
				if (condGunHit5[j]) by5[j] += 1;
			}
			test = true;
		}
		if (test) break;
		}

	for (int i=1;i<width-1;i++){
		bool test = false;
		if(byCond5){
			for (int j=1;j<width-1;j++){
				if(by6[j] == -10) by6[j] = -1;
				if (condGunHit6[j]) by6[j] += 1;
			}
			test = true;
		}
		if (test) break;
		}

	for (int i=1;i<width-1;i++){
		bool test = false;
		if(byCond6){
			for (int j=1;j<width-1;j++){
				if(by7[j] == -10) by7[j] = -1;
				if (condGunHit7[j]) by7[j] += 1;
			}
			test = true;
		}
		if (test) break;
		}

	for (int i=1;i<width-1;i++){
		bool test = false;
		if(byCond7){
			for (int j=1;j<width-1;j++){
				if(by8[j] == -10) by8[j] = -1;
				if (condGunHit8[j]) by8[j] += 1;
			}
			test = true;
		}
		if (test) break;
		}

	if (score != 0 && byCond8 && hitCount >= 18){
		Level += 1;
		Setup();
	}


}

int main()
{
	srand((unsigned int)time(NULL));
    Setup();
    int ip;
    int tempCount = 0;
    cout << "1. Start Game" << endl;
    cout << "2. Exit" << endl;
    cout << "Press 'a' to move Left." <<endl;
    cout << "Press 'd' to move Right." <<endl;
    cout << "Press 'k' to Shoot." <<endl;
    cout << "Press 'l' to Stop Shooting." <<endl;
    cout << "Press 'x' to Exit game." <<endl;
    cout << "Enter you option: ";
    cin  >> ip;
    while(!gameOver)
    {
		Draw();
        Input();
        Logic();
        Sleep(5);
        tempCount++;
        if (tempCount == min((35 - (Level*5)), 35)){
			MoveObs();
			tempCount = 0;
        }
    }
    cout << "Game over!" << endl;
    return 0;
}
