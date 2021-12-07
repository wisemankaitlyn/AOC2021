// Day 7
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

void main()
{
	vector<int> crabs;
	ifstream in;
	in.open("input.txt");

	int c; char temp;
	in >> c >> temp;
	while (!in.eof())
	{
		crabs.push_back(c);
		in >> c >> temp;
	}
	crabs.push_back(c);
	in.close();

	int minFuel = 1000000000;
	int minPos;

	for (int pos = 10; pos < 1500; pos++)
	{
		int currentFuel = 0;
		for (auto p : crabs)
		{
			currentFuel += abs(p - pos);
		}

		if (currentFuel < minFuel)
		{
			minFuel = currentFuel;
			minPos = pos;
		}
	}

	cout << "part 1: the minimum fuel is " << minFuel << " and the minimum position is " << minPos << endl;

	minFuel = 1000000000;
	minPos = 0;

	for (int pos = 10; pos < 1500; pos++)
	{
		int currentFuel = 0;
		for (auto p : crabs)
		{
			currentFuel += (abs(p - pos) * (abs(p - pos) + 1)) / 2;
		}

		if (currentFuel < minFuel)
		{
			minFuel = currentFuel;
			minPos = pos;
		}
	}

	cout << "part 2: the minimum fuel is " << minFuel << " and the minimum position is " << minPos << endl;

	return;
}