// Day 9
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;

const int NUMCOLS = 100;
const int NUMROWS = 100;

struct Pair
{
	int r, c;
	int basinSize = 0;
	vector<vector<int>> m;  // row, col
};

void main()
{
	char heightMap[NUMROWS][NUMCOLS];
	vector<Pair*> p;

	ifstream in;
	in.open("input.txt");

	int col = 0;
	int row = 0;
	char temp;

	while (row < NUMROWS)
	{
		in >> temp;
		heightMap[row][col] = temp - 48;

		col++;
		if (col == NUMCOLS)
		{
			col = 0;
			row++;
		}
	}

	in.close();

	int totalRisk = 0;
	Pair* tempPair = new Pair;

	for (row = 0; row < NUMROWS; row++)
	{
		for (col = 0; col < NUMCOLS; col++)
		{
			// take care of edge cases
			// corner
			if (row == 0 && col == 0)
			{
				if (heightMap[row][col] < heightMap[row + 1][col] && heightMap[row][col] < heightMap[row][col + 1])
				{
					totalRisk += 1 + heightMap[row][col];
					tempPair = new Pair;
					tempPair->c = col;
					tempPair->r = row;
					p.push_back(tempPair);
				}
			}
			else if (row == NUMROWS - 1 && col == 0)
			{
				if (heightMap[row][col] < heightMap[row - 1][col] && heightMap[row][col] < heightMap[row][col + 1])
				{
					totalRisk += 1 + heightMap[row][col];
					tempPair = new Pair;
					tempPair->c = col;
					tempPair->r = row;
					p.push_back(tempPair);
				}
			}
			else if (row == 0 && col == NUMCOLS - 1)
			{
				if (heightMap[row][col] < heightMap[row + 1][col] && heightMap[row][col] < heightMap[row][col - 1])
				{
					totalRisk += 1 + heightMap[row][col];
					tempPair = new Pair;
					tempPair->c = col;
					tempPair->r = row;
					p.push_back(tempPair);
				}
			}
			else if (row == NUMROWS - 1 && col == NUMCOLS - 1)
			{
				if (heightMap[row][col] < heightMap[row - 1][col] && heightMap[row][col] < heightMap[row][col - 1])
				{
					totalRisk += 1 + heightMap[row][col];
					tempPair = new Pair;
					tempPair->c = col;
					tempPair->r = row;
					p.push_back(tempPair);
				}
			}
			else if (row == 0)
			{
				if (heightMap[row][col] < heightMap[row + 1][col]
					&& heightMap[row][col] < heightMap[row][col + 1]
					&& heightMap[row][col] < heightMap[row][col - 1])
				{
					totalRisk += 1 + heightMap[row][col];
					tempPair = new Pair;
					tempPair->c = col;
					tempPair->r = row;
					p.push_back(tempPair);
				}
			}
			else if (row == NUMROWS - 1)
			{
				if (heightMap[row][col] < heightMap[row - 1][col]
					&& heightMap[row][col] < heightMap[row][col + 1]
					&& heightMap[row][col] < heightMap[row][col - 1])
				{
					totalRisk += 1 + heightMap[row][col];
					tempPair = new Pair;
					tempPair->c = col;
					tempPair->r = row;
					p.push_back(tempPair);
				}
			}
			else if (col == 0)
			{
				if (heightMap[row][col] < heightMap[row + 1][col]
					&& heightMap[row][col] < heightMap[row - 1][col]
					&& heightMap[row][col] < heightMap[row][col + 1])
				{
					totalRisk += 1 + heightMap[row][col];
					tempPair = new Pair;
					tempPair->c = col;
					tempPair->r = row;
					p.push_back(tempPair);
				}
			}
			else if (col == NUMCOLS - 1)
			{
				if (heightMap[row][col] < heightMap[row + 1][col]
					&& heightMap[row][col] < heightMap[row - 1][col]
					&& heightMap[row][col] < heightMap[row][col - 1])
				{
					totalRisk += 1 + heightMap[row][col];
					tempPair = new Pair;
					tempPair->c = col;
					tempPair->r = row;
					p.push_back(tempPair);
				}
			}
			else
			{
				// normal space
				if (heightMap[row][col] < heightMap[row + 1][col]
					&& heightMap[row][col] < heightMap[row - 1][col]
					&& heightMap[row][col] < heightMap[row][col + 1]
					&& heightMap[row][col] < heightMap[row][col - 1])
				{
					totalRisk += 1 + heightMap[row][col];
					tempPair = new Pair;
					tempPair->c = col;
					tempPair->r = row;
					p.push_back(tempPair);
				}
			}

		}
	}

	cout << "part 1: the total risk level is " << totalRisk << endl;


	vector<int> basinSizes;

	for (auto l : p)
	{
		// lowest point is first member
		vector<int>* v = new vector<int>;
		v->push_back(l->r);
		v->push_back(l->c);
		l->m.push_back(*v);

		int i = 0;
		bool done = false;
		while (!done)
		{
			// take i-th member of m
			// check above, below, left, and right for new members,
			// and if they're not already in m, push_back

			// check above
			if (l->m.at(i).at(0) > 0)
			{
				v = new vector<int>;
				v->push_back(l->m.at(i).at(0) - 1);
				v->push_back(l->m.at(i).at(1));
				if (heightMap[v->at(0)][v->at(1)] < 9 && find(l->m.begin(), l->m.end(), *v) == l->m.end())
				{
					l->m.push_back(*v);
				}
			}

			// check below
			if (l->m.at(i).at(0) < NUMROWS - 1)
			{
				v = new vector<int>;
				v->push_back(l->m.at(i).at(0) + 1);
				v->push_back(l->m.at(i).at(1));
				if (heightMap[v->at(0)][v->at(1)] < 9 && find(l->m.begin(), l->m.end(), *v) == l->m.end())
				{
					l->m.push_back(*v);
				}
			}

			// check left
			if (l->m.at(i).at(1) > 0)
			{
				v = new vector<int>;
				v->push_back(l->m.at(i).at(0));
				v->push_back(l->m.at(i).at(1) - 1);
				if (heightMap[v->at(0)][v->at(1)] < 9 && find(l->m.begin(), l->m.end(), *v) == l->m.end())
				{
					l->m.push_back(*v);
				}
			}

			// check right
			if (l->m.at(i).at(1) < NUMCOLS - 1)
			{
				v = new vector<int>;
				v->push_back(l->m.at(i).at(0));
				v->push_back(l->m.at(i).at(1) + 1);
				if (heightMap[v->at(0)][v->at(1)] < 9 && find(l->m.begin(), l->m.end(), *v) == l->m.end())
				{
					l->m.push_back(*v);
				}
			}

			i++;
			if (i >= l->m.size())
			{
				done = true;
			}
		}

		basinSizes.push_back(l->m.size());
	}

	sort(basinSizes.begin(), basinSizes.end(), greater <>());

	cout << "part 2: the product of the three largest basins is " << basinSizes.at(0) * basinSizes.at(1) * basinSizes.at(2);
	
	return;
}