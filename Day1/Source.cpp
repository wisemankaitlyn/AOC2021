// Day 1
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

void main()
{
	// part 1

	vector<int> depths;
	ifstream in;
	in.open("input.txt");

	int lastTemp, temp, numInc = 0;

	in >> lastTemp;
	while (!in.eof())
	{
		in >> temp;
		if (temp > lastTemp) numInc++;

		lastTemp = temp;
	}
	in.close();

	cout << "Part 1: the number of increases is " << numInc << endl;

	// part 2

	int sum, lastSum = 0;
	temp, numInc = 0;

	in.open("input.txt");
	while (!in.eof())
	{
		in >> temp;
		depths.push_back(temp);
	}
	in.close();

	lastSum = depths.at(0) + depths.at(1) + depths.at(2);
	for (int i = 1; i + 2 < depths.size(); i++)
	{
		sum = depths.at(i) + depths.at(i + 1) + depths.at(i + 2);

		if (sum > lastSum) numInc++;
		lastSum = sum;
	}

	cout << "Part 2: the number of increases is " << numInc << endl;

	return;
}