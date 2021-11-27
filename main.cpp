#include <iostream>
#include <cstring>
#define CLRSCR "\e[2J\e[H";
#define RED "\x1b[31m";
#define BLUE "\x1b[34m";
#define MAGENTA "\x1b[35m";
#define WHITE "\x1b[37m";
#define GREEN "\x1b[32m";
using namespace std;
int SIDE; 
int MINES; 

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
	cout<<"Enter the coordinates(row, column): ";
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

int main()
{
	getInput();
	playGame();
}