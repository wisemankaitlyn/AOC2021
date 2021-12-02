// Day 2
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

void main()
{
	ifstream in;
	in.open("input.txt");

	string direction;
	int horiz = 0;
	int depth = 0;
	int amount;
	while (!in.eof())
	{
		in >> direction;
		in >> amount;

		if (direction == "forward")
		{
			horiz += amount;
		}
		else if (direction == "down")
		{
			depth += amount;
		}
		else if (direction == "up")
		{
			depth -= amount;
		}
	}
	in.close();

	cout << "part 1: horiz * depth = " << horiz * depth << endl;

	// part 2
	in.open("input.txt");

	horiz = 0;
	depth = 0;
	int aim = 0;
	while (!in.eof())
	{
		in >> direction;
		in >> amount;

		if (direction == "forward")
		{
			horiz += amount;
			depth += aim * amount;
		}
		else if (direction == "down")
		{
			aim += amount;
		}
		else if (direction == "up")
		{
			aim -= amount;
		}
	}
	in.close();

	cout << "part 2: horiz * depth = " << horiz * depth << endl;

	return;
}