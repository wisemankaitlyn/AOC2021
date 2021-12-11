// Day 11
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

const int NUMCOLS = 10;
const int NUMROWS = 10;

char map[NUMROWS][NUMCOLS];

void flash(int i, int j);
long numFlashes = 0;

void main()
{
	int FirstDayAllFlashed = -1;
	ifstream in;
	in.open("input.txt");

	for (int i = 0; i < NUMROWS; i++)
	{
		for (int j = 0; j < NUMCOLS; j++)
		{
			char temp;
			in >> temp;
			map[i][j] = temp - 48;
		}
	}
	in.close();

	for (int day = 0; day < 100; day++)
	{
		// increment each space
		for (int i = 0; i < NUMROWS; i++)
		{
			for (int j = 0; j < NUMROWS; j++)
			{
				map[i][j]++;
			}
		}	

		// check for 9's
		for (int i = 0; i < NUMROWS; i++)
		{
			for (int j = 0; j < NUMROWS; j++)
			{
				if (map[i][j] > 9)
				{
					flash(i, j);
				}
			}
		}

		// set all the -1's to 0
		int numFlashedThisRound = 0;
		for (int i = 0; i < NUMROWS; i++)
		{
			for (int j = 0; j < NUMCOLS; j++)
			{
				if (map[i][j] == -1)
				{
					map[i][j] = 0;
					numFlashedThisRound++;
				}

			}
		}
		if (numFlashedThisRound == NUMROWS * NUMCOLS && FirstDayAllFlashed == -1) FirstDayAllFlashed = day + 1;
	}

	cout << "part 1: after 100 days, the number of flashes is " << numFlashes << endl;


	for (int day = 100; true; day++)
	{
		// increment each space
		for (int i = 0; i < NUMROWS; i++)
		{
			for (int j = 0; j < NUMROWS; j++)
			{
				map[i][j]++;
			}
		}

		// check for 9's
		for (int i = 0; i < NUMROWS; i++)
		{
			for (int j = 0; j < NUMROWS; j++)
			{
				if (map[i][j] > 9)
				{
					flash(i, j);
				}
			}
		}

		// set all the -1's to 0
		int numFlashedThisRound = 0;
		for (int i = 0; i < NUMROWS; i++)
		{
			for (int j = 0; j < NUMCOLS; j++)
			{
				if (map[i][j] == -1)
				{
					map[i][j] = 0;
					numFlashedThisRound++;
				}

			}
		}
		if (numFlashedThisRound == NUMROWS * NUMCOLS && FirstDayAllFlashed == -1)
		{
			FirstDayAllFlashed = day + 1;
			break;
		}
	}

	cout << "part 2: the first day all octopi flashed is " << FirstDayAllFlashed << endl;
}

void flash(int i, int j)
{
	numFlashes++;
	map[i][j] = -1;

	// UL
	if (i > 0 && j > 0)
	{
		if (map[i - 1][j - 1] != -1)
		{
			map[i - 1][j - 1]++;
			if (map[i - 1][j - 1] > 9) flash(i - 1, j - 1);
		}
	}
	// UM
	if (i > 0)
	{
		if (map[i - 1][j] != -1)
		{
			map[i - 1][j]++;
			if (map[i - 1][j] > 9) flash(i - 1, j);
		}
	}
	// UR
	if (i > 0 && j < NUMCOLS - 1)
	{
		if (map[i - 1][j + 1] != -1)
		{
			map[i - 1][j + 1]++;
			if (map[i - 1][j + 1] > 9) flash(i - 1, j + 1);
		}
	}
	// ML
	if (j > 0)
	{
		if (map[i][j - 1] != -1)
		{
			map[i][j - 1]++;
			if (map[i][j - 1] > 9) flash(i, j - 1);
		}
	}
	// MR
	if (j < NUMCOLS - 1)
	{
		if (map[i][j + 1] != -1)
		{
			map[i][j + 1]++;
			if (map[i][j + 1] > 9) flash(i, j + 1);
		}
	}
	// LL
	if (i < NUMROWS - 1 && j > 0)
	{
		if (map[i + 1][j - 1] != -1)
		{
			map[i + 1][j - 1]++;
			if (map[i + 1][j - 1] > 9) flash(i + 1, j - 1);
		}
	}
	// LM
	if (i < NUMROWS - 1)
	{
		if (map[i + 1][j] != -1)
		{
			map[i + 1][j]++;
			if (map[i + 1][j] > 9) flash(i + 1, j);
		}
	}
	// LR
	if (i < NUMROWS - 1 && j < NUMCOLS - 1)
	{
		if (map[i + 1][j + 1] != -1)
		{
			map[i + 1][j + 1]++;
			if (map[i + 1][j + 1] > 9) flash(i + 1, j + 1);
		}
	}
}