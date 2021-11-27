#include <iostream>
#include <cstring>
#include <unistd.h>
#define CLRSCR "\e[2J\e[H";
#define RED "\x1b[31m";
#define BLUE "\x1b[34m";
#define MAGENTA "\x1b[35m";
#define WHITE "\x1b[37m";
#define GREEN "\x1b[32m";
#define T "\t\t\t\t\t\t\t";
using namespace std;
int SIDE; 
int MINES;
void Intro();
void Rules();
void Exit(); 

bool isValid(int row, int col)
{
	return ((row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE));
}

bool isMine(int row, int col, char board[][25])
{
	if (board[row][col] == '*')
		return true;
	else
		return false;
}

void getInput(int *x, int *y)
{
	cout<<"Enter the coordinates (Row(x), Column(y)): ";
	cin>>*x;
	cin>>*y;
	cout<<CLRSCR;
}

void printBoard(char myBoard[][25])
{
	cout<<MAGENTA;
	cout<<"Board: "<<endl<<endl;
	cout<<WHITE;
	cout<<"  ";
	for(int i = 0; i < SIDE; i++)
	{
		cout<<BLUE;
		cout<<" "<<i;
		cout<<WHITE;
	}
	cout<<endl;
	for (int i = 0; i < SIDE; i++)
	{
		cout<<BLUE;
		cout<<" "<<i;
		cout<<WHITE;
		for(int j = 0; j < SIDE; j++)
		{
			if(myBoard[i][j] == '*')
			{
				cout<<RED;
			}
			else if(myBoard[i][j] == '-')
			{
				cout<<WHITE;
			}
			else
			{
				cout<<GREEN;
			}
			cout<<" "<<myBoard[i][j];
			cout<<WHITE;
		}
		cout<<endl;
	}
	cout<<endl;
}

int countMines(int row, int col, int mines[][2],  char realBoard[][25])
{
	int count = 0;

	if(isValid(row-1, col) && (isMine(row-1, col, realBoard)))
	{
		count++;
	}

	if(isValid(row+1, col) && (isMine(row+1, col, realBoard)))
	{
		count++;
	}

	if(isValid(row, col+1) && (isMine(row, col+1, realBoard)))
	{
		count++;
	}

	if(isValid(row, col-1) && (isMine(row, col-1, realBoard)))
	{
		count++;
	}

	if(isValid(row-1, col+1) && (isMine(row-1, col+1, realBoard)))
	{
		count++;
	}

	if(isValid(row-1, col-1) && (isMine(row-1, col-1, realBoard)))
	{
		count++;
	}

	if(isValid(row+1, col+1) && (isMine(row+1, col+1, realBoard)))
	{
		count++;
	}

	if(isValid(row+1, col-1) && (isMine(row+1, col-1, realBoard)))
	{
		count++;
	}

	return count;
}

bool playUntil(char myBoard[][25], char realBoard[][25], int mines[][2], int row, int col, int *movesLeft)
{

	if (myBoard[row][col] != '-')
		return false;

	if (realBoard[row][col] == '*')
	{
		myBoard[row][col]='*';

		for (int i = 0; i < MINES; i++)
		{
			myBoard[mines[i][0]][mines[i][1]] = '*';
		}
		
		printBoard(myBoard);
		cout<<RED;
		cout<<"OH NO! You stepped on a MINE! "<<endl;
		cout<<"\t\tGAME OVER! "<<endl;
		cout<<WHITE;
		return true;
	}
	else
	{
		int count = countMines(row, col, mines, realBoard);
		(*movesLeft)--;
	
		myBoard[row][col] = count + '0';
		
		if(!count)
		{
			if(isValid(row-1, col) && (!isMine(row-1, col, realBoard)))
			{
				playUntil(myBoard, realBoard, mines, row-1, col, movesLeft);
			}

			if(isValid(row+1, col) && (!isMine(row+1, col, realBoard)))
			{
				playUntil(myBoard, realBoard, mines, row+1, col, movesLeft);
			}

			if(isValid(row, col+1) && (!isMine(row, col+1, realBoard)))
			{
				playUntil(myBoard, realBoard, mines, row, col+1, movesLeft);
			}

			if(isValid(row, col-1) && (!isMine(row, col-1, realBoard)))
			{
				playUntil(myBoard, realBoard, mines, row, col-1, movesLeft);
			}

			if(isValid(row-1, col+1) && (!isMine(row-1, col+1, realBoard)))
			{
				playUntil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
			}

			if(isValid(row-1, col-1) && (!isMine(row-1, col-1, realBoard)))
			{
				playUntil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
			}

			if(isValid(row+1, col+1) && (!isMine(row+1, col+1, realBoard)))
			{
				playUntil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
			}

			if(isValid(row+1, col-1) && (!isMine(row+1, col-1, realBoard)))
			{
				playUntil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
			}
		}
		return false;
	}
}

void placeMines(int mines[][2], char realBoard[][25])
{
	bool mark[25 * 25];
	memset(mark, false, sizeof (mark));

	for (int i = 0; i < MINES; )
	{
		int ran = rand() % (SIDE*SIDE);
		int x = ran / SIDE;
		int y = ran % SIDE;

		if (!mark[ran])
		{
			mines[i][0]= x;
			mines[i][1] = y;

			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[ran] = true;
			i++;
		}
	}
}

void initialise(char realBoard[][25], char myBoard[][25])
{
	srand(time(NULL));

	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}
}

void getMineLocation(char realBoard[][25])
{
	cout<<"Mine Locations are: ";
	printBoard(realBoard);
}

void replaceMine(int row, int col, char board[][25])
{
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] != '*')
			{
				board[i][j] = '*';
				board[row][col] = '-';
				return;
			}
		}
	}
}

void playGame()
{
	bool gameOver = false;

	char realBoard[25][25], myBoard[25][25];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[99][2]; 

	initialise (realBoard, myBoard);

	placeMines (mines, realBoard);
	//getMineLocation(realBoard);
	
	int moveCount = 0;
	while(!gameOver)
	{
		printBoard(myBoard);
		getInput(&x, &y);

		if(moveCount == 0)
		{
			if(isMine (x, y, realBoard))
			{
				replaceMine (x, y, realBoard);
			}
		}
		moveCount ++;
		gameOver = playUntil(myBoard, realBoard, mines, x, y, &movesLeft);

		if ((!gameOver) && (movesLeft == 0))
		{
			printBoard(myBoard);
			cout<<GREEN;
			cout<<"******************** YOU WON! ********************"<<endl;
			cout<<WHITE;
			gameOver = true;
		}
	}
}

void getInput()
{
	cout<<CLRSCR;
	cout<<"Enter number of sides for board: ";
	cin>>SIDE;

	cout<<"Enter number of mines: ";
	cin>>MINES;
	cout<<endl;
	cout<<CLRSCR;
}

void Rules()
{
	char back;
	cout<<CLRSCR;
	cout<<"RULES: "<<endl<<endl;
	cout<<"1) The board is divided into cells, with mines randomly distributed. "<<endl;
	cout<<"2) To win, you need to open all the cells. "<<endl;
	cout<<"3) The number on a cell indicates the number of mines adjacent to it. "<<endl;
	cout<<"4) Using this you can determine which cells are safe and which contain mines. "<<endl<<endl;
	cout<<"Press B to go back: ";
	cin>>back;
	if(back == 'b' || back == 'B')
	{
		Intro();
	}
	else
	{
		cout<<RED;
		cout<<"Please press b to go to the main menu! "<<endl<<WHITE;
		sleep(2);
		Rules();
	}
}

void Exit()
{
	char choice;
	cout<<endl<<RED;
	cout<<"\t\t\t\t Do you want to exit the game (Y/N): ";
	cin>>choice;
	if(choice == 'y' || choice == 'Y')
	{
		cout<<RED;
		cout<<T;cout<<"\tBYE!"<<endl<<WHITE;
		sleep(2);
		return;
	}
	else if(choice == 'n' || choice == 'N')
	{
		Intro();
	}
	else
	{
		cout<<RED;
		cout<<"Please press Y for Yes or N for No! "<<endl<<WHITE;
		sleep(2);
		Exit();
	}
}

void Intro()
{
	int choice;
	while(true)
	{
		cout<<CLRSCR;
		cout<<MAGENTA;
		cout<<"               _"<<endl;
		cout<<"   ____ ___   (_)____   ___   _____ _      __ ___   ___   ____   ___   _____"<<endl;
		cout<<"  / __ `__ \\ / // __ \\ / _ \\ / ___/| | /\\ / // _ \\ / _ \\ / __ \\ / _ \\ / ___/"<<endl;
		cout<<" / / / / / // // / / //  __/(__  ) | |/ \\/ //  __//  __// /_/ //  __// /"<<endl;
		cout<<"/_/ /_/ /_//_//_/ /_/ \\___/ \\___/  \\__/\\__/ \\___/ \\___// .___/ \\___//_/"<<endl;
		cout<<"                                                      /_/"<<endl<<endl;
		cout<<GREEN;
		cout<<T;cout<<" 0 0 1 1 1"<<endl;
		cout<<T;cout<<" 0 0 1 ";cout<<RED;cout<<"*"<<GREEN;cout<<" 1"<<endl;
		cout<<T;cout<<" 1 1 2 2 2"<<endl<<RED;
		cout<<T;cout<<" *"<<GREEN;cout<<" 1 1 "<<RED;cout<<"*"<<GREEN;cout<<" 2"<<endl;
		cout<<T;cout<<" 1 1 1 2 "<<RED;cout<<"*"<<endl<<endl<<WHITE;
		cout<<T;cout<<"  1) PLAY "<<endl;
		cout<<T;cout<<"  2) RULES "<<endl;
		cout<<T;cout<<"  3) EXIT "<<endl<<endl;
		cout<<"\t\t\t\t\t\t Enter your Input: ";
		cin>>choice;
		if(choice == 1)
		{
			getInput();
			playGame();
			break;
		}
		else if(choice == 2)
		{
			Rules();
			break;
		}
		else if(choice == 3)
		{
			Exit();
			break;
		}
		else
		{
			cout<<RED;
			cout<<"\t\t\t\t\t  Please Enter a valid Choice! "<<WHITE;
			sleep(2);
		}
	}
}

int main()
{	
	Intro();	
}