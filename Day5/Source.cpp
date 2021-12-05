// Day 5
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

struct line
{
	int x1, y1, x2, y2;
};

void main()
{
	ifstream in;
	in.open("input.txt");

	int x1, y1, x2, y2;
	char hits[1000][1000] = { 0x00 };
	char temp;

	vector<line*> lines;

	line* tempLine = new line;

	in >> tempLine->x1 >> temp >> tempLine->y1 >> temp >> temp >> tempLine->x2 >> temp >> tempLine->y2;
	while (!in.eof())
	{
		lines.push_back(tempLine);

		tempLine = new line;
		in >> tempLine->x1 >> temp >> tempLine->y1 >> temp >> temp >> tempLine->x2 >> temp >> tempLine->y2;
	}
	lines.push_back(tempLine);
	in.close();

	int numHitTwice = 0;

	for (auto l : lines)
	{
		if (l->x1 == l->x2)
		{
			if (l->y1 > l->y2)
			{
				for (int i = l->y2; i <= l->y1; i++)
				{
					hits[l->x1][i]++;
					if (hits[l->x1][i] == 2) 
						numHitTwice++;
				}
			}
			else
			{
				for (int i = l->y1; i <= l->y2; i++)
				{
					hits[l->x1][i]++;
					if (hits[l->x1][i] == 2) 
						numHitTwice++;
				}
			}
		}
		else if (l->y1 == l->y2)
		{
			if (l->x1 > l->x2)
			{
				for (int i = l->x2; i <= l->x1; i++)
				{
					hits[i][l->y1]++;
					if (hits[i][l->y1] == 2) 
						numHitTwice++;
				}
			}
			else
			{
				for (int i = l->x1; i <= l->x2; i++)
				{
					hits[i][l->y1]++;
					if (hits[i][l->y1] == 2) 
						numHitTwice++;
				}
			}
		}
		else // diagonals
		{
			if (l->x1 > l->x2)
			{
				if (l->y1 > l->y2)
				{
					for (int i = 0; i <= (l->x1 - l->x2); i++)
					{
						hits[l->x2 + i][l->y2 + i]++;
						if (hits[l->x2 + i][l->y2 + i] == 2) numHitTwice++;
					}
				}
				else
				{
					for (int i = 0; i <= (l->x1 - l->x2); i++)
					{
						hits[l->x2 + i][l->y2 - i]++;
						if (hits[l->x2 + i][l->y2 - i] == 2) numHitTwice++;
					}
				}
			}
			else
			{
				if (l->y1 > l->y2)
				{
					for (int i = 0; i <= (l->x2 - l->x1); i++)
					{
						hits[l->x2 - i][l->y2 + i]++;
						if (hits[l->x2 - i][l->y2 + i] == 2) numHitTwice++;
					}
				}
				else
				{
					for (int i = 0; i <= (l->x2 - l->x1); i++)
					{
						hits[l->x2 - i][l->y2 - i]++;
						if (hits[l->x2 - i][l->y2 - i] == 2) numHitTwice++;
					}
				}
			}
		}
	}

	cout << "part 2: the number of spaces hit at least twice is " << numHitTwice << endl;

	return;

}