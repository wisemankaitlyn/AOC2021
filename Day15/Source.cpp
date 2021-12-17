// Day 15
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

const int NUMROWS = 100;
const int NUMCOLS = 100;
const int NUMROWS2 = NUMROWS * 5;
const int NUMCOLS2 = NUMCOLS * 5;

struct hmm
{
	int a[NUMROWS2][NUMCOLS2];
};

void main()
{
	char map[NUMROWS][NUMCOLS];
	
	if (true)
	{
		int tentativeDistance[NUMROWS][NUMCOLS];
		for (int i = 0; i < NUMROWS; i++)
		{
			for (int j = 0; j < NUMCOLS; j++)
			{
				tentativeDistance[i][j] = 2147483647;
			}
		}
		tentativeDistance[0][0] = 0;
		bool visited[NUMROWS][NUMCOLS] = { false };

		ifstream in;
		in.open("input.txt");

		int row = 0;
		int col = 0;
		while (row < NUMROWS)
		{
			char temp;
			in >> temp;
			map[row][col] = temp - 48;

			col++;
			if (col >= NUMCOLS)
			{
				col = 0;
				row++;
			}
		}
		in.close();

		row = 0;
		col = 0;

		bool done = false;

		while (!done)
		{
			// consider all of the unvisited neighbors

			// north
			if (row > 0 && !visited[row - 1][col])
			{
				int newTentativeDistance = tentativeDistance[row][col] + map[row - 1][col];

				if (newTentativeDistance < tentativeDistance[row - 1][col])
					tentativeDistance[row - 1][col] = newTentativeDistance;
			}

			// south
			if (row < NUMROWS - 1 && !visited[row + 1][col])
			{
				int newTentativeDistance = tentativeDistance[row][col] + map[row + 1][col];

				if (newTentativeDistance < tentativeDistance[row + 1][col])
					tentativeDistance[row + 1][col] = newTentativeDistance;
			}

			// east
			if (col < NUMCOLS - 1 && !visited[row][col + 1])
			{
				int newTentativeDistance = tentativeDistance[row][col] + map[row][col + 1];

				if (newTentativeDistance < tentativeDistance[row][col + 1])
					tentativeDistance[row][col + 1] = newTentativeDistance;
			}

			// west
			if (col > 0 && !visited[row][col - 1])
			{
				int newTentativeDistance = tentativeDistance[row][col] + map[row][col - 1];

				if (newTentativeDistance < tentativeDistance[row][col - 1])
					tentativeDistance[row][col - 1];
			}


			// mark the current node as visited
			visited[row][col] = true;

			int nextRow, nextCol;
			int smallestTentativeDistance = 2147483647;

			// select the next node
			for (int rowInd = 0; rowInd < NUMROWS; rowInd++)
			{
				for (int colInd = 0; colInd < NUMCOLS; colInd++)
				{
					if (!visited[rowInd][colInd])
					{
						if (tentativeDistance[rowInd][colInd] < smallestTentativeDistance)
						{
							nextRow = rowInd;
							nextCol = colInd;
							smallestTentativeDistance = tentativeDistance[rowInd][colInd];
						}
					}
				}
			}

			row = nextRow;
			col = nextCol;

			// check if we're done -- if the destination node has been selected
			done = (row == NUMROWS - 1 && col == NUMCOLS - 1);
		}

		cout << "Part 1: the lowest total risk of any path is " << tentativeDistance[NUMROWS - 1][NUMCOLS - 1] << endl;
	}

	char map2[NUMROWS2][NUMCOLS2];

	/*for (int r = 0; r < NUMROWS; r++)
	{
		for (int c = 0; c < NUMCOLS; c++)
		{
			cout << int(map[r][c]);
		}
		cout << endl;
	}*/


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int r = 0; r < NUMROWS; r++)
			{
				for (int c = 0; c < NUMCOLS; c++)
				{
					map2[r + i*NUMROWS][c + j*NUMCOLS] = map[r][c] + i + j;

					if (map2[r + i * NUMROWS][c + j * NUMCOLS] > 9) 
						map2[r + i * NUMROWS][c + j * NUMCOLS] = map2[r + i * NUMROWS][c + j * NUMCOLS] - 9;

					//cout << int(map2[r + i * NUMROWS][c + j * NUMCOLS]);
				}
				//cout << "|" << endl;
			}
			/*cout << endl;
			cout << "---------------------------------------------------------" << endl;*/
		}
	}

	hmm* tentativeDistance = new hmm;
	for (int i = 0; i < NUMROWS2; i++)
	{
		for (int j = 0; j < NUMCOLS2; j++)
		{
			tentativeDistance->a[i][j] = 2147483647;
		}
	}
	tentativeDistance->a[0][0] = 0;
	bool visited[NUMROWS2][NUMCOLS2] = { false };

	int row = 0;
	int col = 0;

	bool done = false;

	while (!done)
	{
		// consider all of the unvisited neighbors

		// north
		if (row > 0 && !visited[row - 1][col])
		{
			int newTentativeDistance = tentativeDistance->a[row][col] + map2[row - 1][col];

			if (newTentativeDistance < tentativeDistance->a[row - 1][col])
				tentativeDistance->a[row - 1][col] = newTentativeDistance;
		}

		// south
		if (row < NUMROWS2 - 1 && !visited[row + 1][col])
		{
			int newTentativeDistance = tentativeDistance->a[row][col] + map2[row + 1][col];

			if (newTentativeDistance < tentativeDistance->a[row + 1][col])
				tentativeDistance->a[row + 1][col] = newTentativeDistance;
		}

		// east
		if (col < NUMCOLS2 - 1 && !visited[row][col + 1])
		{
			int newTentativeDistance = tentativeDistance->a[row][col] + map2[row][col + 1];

			if (newTentativeDistance < tentativeDistance->a[row][col + 1])
				tentativeDistance->a[row][col + 1] = newTentativeDistance;
		}

		// west
		if (col > 0 && !visited[row][col - 1])
		{
			int newTentativeDistance = tentativeDistance->a[row][col] + map2[row][col - 1];

			if (newTentativeDistance < tentativeDistance->a[row][col - 1])
				tentativeDistance->a[row][col - 1] = newTentativeDistance;
		}

		// mark the current node as visited
		visited[row][col] = true;

		int nextRow = row, nextCol = col;
		int smallestTentativeDistance = 2147483647;

		// select the next node
		for (int rowInd = 0; rowInd < NUMROWS2; rowInd++)
		{
			for (int colInd = 0; colInd < NUMCOLS2; colInd++)
			{
				if (!visited[rowInd][colInd])
				{
					if (tentativeDistance->a[rowInd][colInd] < smallestTentativeDistance)
					{
						nextRow = rowInd;
						nextCol = colInd;
						smallestTentativeDistance = tentativeDistance->a[rowInd][colInd];
					}
				}
			}
		}

		row = nextRow;
		col = nextCol;

		// check if we're done -- if the destination node has been selected
		done = (row == NUMROWS2 - 1 && col == NUMCOLS2 - 1);
	}

	cout << "part 2: the lowest total risk of any path is " << tentativeDistance->a[NUMROWS2 - 1][NUMCOLS2 - 1] << endl;

	return;
}