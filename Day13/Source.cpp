// Day 13
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

struct Fold
{
	bool alongX;
	int line;
};

void main()
{
	ifstream in;
	in.open("input.txt");

	vector<vector<char>> paper;
	vector<Fold*> folds;

	vector<int> xCoords;
	vector<int> yCoords;
	for (int i = 0; i < /*18*/ 866; i++)
	{
		int tempX, tempY;
		char tempChar;
		in >> tempX >> tempChar >> tempY;

		xCoords.push_back(tempX);
		yCoords.push_back(tempY);
	}

	int maxX = *(max_element(xCoords.begin(), xCoords.end()));
	int maxY = *(max_element(yCoords.begin(), yCoords.end()));

	// generate map
	vector<char> paperLine(maxX + 1, '.');
	for (int i = 0; i < maxY + 1; i++)
	{
		paper.push_back(paperLine);
	}

	// put initial dots on the paper
	for (int i = 0; i < xCoords.size(); i++)
	{
		paper.at(yCoords.at(i)).at(xCoords.at(i)) = '#';
	}

	// get folds
	while (!in.eof())
	{
		string tempString;
		char xOrY, tempChar;
		int foldLine;
		in >> tempString >> tempString >> xOrY >> tempChar >> foldLine;

		Fold* tempFold = new Fold;
		tempFold->alongX = (xOrY == 'x');
		tempFold->line = foldLine;

		folds.push_back(tempFold);
	}

	// perform first fold
	if (folds.at(0)->alongX)
	{
		// fold along the x-axis
		vector<vector<char>> nextPaper;
		
		for (int i = 0; i < paper.size(); i++)
		{
			paperLine.clear();
			paperLine.assign(paper.at(i).begin() + folds.at(0)->line + 1, paper.at(i).end());

			nextPaper.push_back(paperLine);

			for (int j = folds.at(0)->line - 1; j >= 0; j--)
			{
				if (paper.at(i).at(j) == '#')
				{
					nextPaper.at(i).at(folds.at(0)->line - 1 - j) = '#';
				}
			}
		}

		paper = nextPaper;
	}
	else
	{
		// fold along the y-axis
		vector<vector<char>> nextPaper;

		for (int i = 0; i < folds.at(0)->line; i++)
		{
			nextPaper.push_back(paper.at(i));

			for (int j = 0; j < nextPaper.at(i).size(); j++)
			{
				if (folds.at(0)->line + folds.at(0)->line - i >= 0 && folds.at(0)->line + folds.at(0)->line - i < paper.size())
					if (paper.at(folds.at(0)->line + folds.at(0)->line - i).at(j) == '#')
					{
						nextPaper.at(i).at(j) = '#';
					}
			}
		}

		paper = nextPaper;
	}

	int numDots = 0;
	for (auto line : paper)
	{
		for (auto c : line)
		{
			if (c == '#') numDots++;

			//cout << c;
		}
		//cout << endl;
	}

	cout << "part 1: the number of dots after the first fold is " << numDots << endl;


	for (int foldIndex = 1; foldIndex < folds.size(); foldIndex++)
	{
		if (folds.at(foldIndex)->alongX)
		{
			// fold along the x-axis
			vector<vector<char>> nextPaper;

			for (int i = 0; i < paper.size(); i++)
			{
				paperLine.clear();
				paperLine.assign(paper.at(i).begin() + folds.at(foldIndex)->line + 1, paper.at(i).end());

				nextPaper.push_back(paperLine);

				for (int j = folds.at(foldIndex)->line - 1; j >= 0; j--)
				{
					if (paper.at(i).at(j) == '#')
					{
						nextPaper.at(i).at(folds.at(foldIndex)->line - 1 - j) = '#';
					}
				}
			}

			paper = nextPaper;
		}
		else
		{
			// fold along the y-axis
			vector<vector<char>> nextPaper;

			for (int i = 0; i < folds.at(foldIndex)->line; i++)
			{
				nextPaper.push_back(paper.at(i));

				for (int j = 0; j < nextPaper.at(i).size(); j++)
				{
					if (folds.at(foldIndex)->line + folds.at(foldIndex)->line - i >= 0 && folds.at(foldIndex)->line + folds.at(foldIndex)->line - i < paper.size())
						if (paper.at(folds.at(foldIndex)->line + folds.at(foldIndex)->line - i).at(j) == '#')
						{
							nextPaper.at(i).at(j) = '#';
						}
				}
			}

			paper = nextPaper;
		}
	}

	for (auto line : paper)
	{
		reverse(line.begin(), line.end());
		for (auto c : line)
		{
			cout << c;
		}
		cout << endl;
	}

	return;

}