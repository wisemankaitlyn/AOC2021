// Day 4
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

struct bingoBoard
{
	int board[5][5];
	bool hits[5][5] = { false };
	bool won = false;
};

bool checkBoard(bingoBoard* b, int bingoNumber);

void main()
{
	vector<int> bingoNumbers;
	vector<bingoBoard*> boards;

	ifstream in;
	in.open("input.txt");

	char temp;
	int currentNumber;

	in >> currentNumber;
	in >> temp;

	while (temp == ',')
	{
		bingoNumbers.push_back(currentNumber);

		in >> currentNumber >> temp;
	}

	bingoNumbers.push_back(currentNumber);

	int x = 0;
	int y = 0;

	bingoBoard* currentBoard = new bingoBoard;
	in >> currentNumber;

	while (!in.eof())
	{
		currentBoard->board[y][x] = currentNumber;
		x++;
		if (x >= 5)
		{
			x = 0;
			y++;
		}
		if (y >= 5)
		{
			y = 0;
			boards.push_back(currentBoard);
			currentBoard = new bingoBoard;
		}

		in >> currentNumber;
	}
	currentBoard->board[y][x] = currentNumber;
	boards.push_back(currentBoard);

	// game
	bool gameOver = false;
	int winnerIndex;
	int bingoNumberIndex = 0;

	while (1)
	{
		// pull new number
		// look at bingoNumbers.at(bingoNumbersIndex);

		// check boards
		for (int boardIndex = 0; boardIndex < boards.size(); boardIndex++)
		{
			gameOver = checkBoard(boards.at(boardIndex), bingoNumbers.at(bingoNumberIndex));
			if (gameOver)
			{
				winnerIndex = boardIndex;
				boards.at(boardIndex)->won = true;
				break;
			}
		}
		if (gameOver) break;

		bingoNumberIndex++;
	}

	// calculate score
	int score = 0;
	bingoBoard* b = boards.at(winnerIndex);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!b->hits[i][j]) score += b->board[i][j];
		}
	}

	score *= bingoNumbers.at(bingoNumberIndex);

	cout << "part 1: the winning score is " << score << endl;

	// part 2
	// continue i guess
	// don't update bingoNumberIndex in case we didn't get through it all
	int lastLost;
	while (1)
	{
		// pull new number
		// look at bingoNumbers.at(bingoNumbersIndex);

		// check boards
		for (int boardIndex = 0; boardIndex < boards.size(); boardIndex++)
		{
			if (!(boards.at(boardIndex)->won))
				boards.at(boardIndex)->won = checkBoard(boards.at(boardIndex), bingoNumbers.at(bingoNumberIndex));
		}
		int numWon = 0;
		for (int boardIndex = 0; boardIndex < boards.size(); boardIndex++)
		{
			if (boards.at(boardIndex)->won) numWon++;
			else lastLost = boardIndex;
		}
		if (numWon == boards.size() - 1) break;

		bingoNumberIndex++;
	}

	while (!(boards.at(lastLost)->won))
	{
		bingoNumberIndex++;
		boards.at(lastLost)->won = checkBoard(boards.at(lastLost), bingoNumbers.at(bingoNumberIndex));
	}

	score = 0;
	b = boards.at(lastLost);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!b->hits[i][j]) score += b->board[i][j];
		}
	}

	score *= bingoNumbers.at(bingoNumberIndex);

	cout << "part 2: the losing score is " << score << endl;
}

bool checkBoard(bingoBoard* b, int bingoNumber)
{
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (b->board[y][x] == bingoNumber)
			{
				b->hits[y][x] = true;
			}
		}
	}

	// check for win
	bool won = false;

	for (int i = 0; i < 5; i++)
	{
		won = won || (b->hits[i][0] && b->hits[i][1] && b->hits[i][2] && b->hits[i][3] && b->hits[i][4]);
		won = won || (b->hits[0][i] && b->hits[1][i] && b->hits[2][i] && b->hits[3][i] && b->hits[4][i]);
	}

	return won;
}