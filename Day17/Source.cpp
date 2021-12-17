// Day 17
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

const int MAX_X = 202;
const int MIN_X = 156;
const int MAX_Y = -69;
const int MIN_Y = -110;

int simulate(int xVel, int yVel);

void main()
{
	int maxYFound = 0;
	int numInitVelVals = 0;

	for (int xVel = 0; xVel <= MAX_X; xVel++)
	{
		for (int yVel = MIN_Y - 1; yVel < 1000; yVel++)
		{
			int currentYFound = simulate(xVel, yVel);

			if (currentYFound > maxYFound) maxYFound = currentYFound;

			if (currentYFound != -1) numInitVelVals++;
		}
	}

	cout << "the max y coordinate found is " << maxYFound << endl;

	cout << "the number of distinct initial velocity values that cause the probe to hit is " << numInitVelVals << endl;
}


int simulate(int xVel, int yVel)
{
	int x = 0;
	int y = 0;
	int maxY = 0;

	while (true)
	{
		x += xVel;
		y += yVel;
		if      (xVel > 0) xVel -= 1;
		else if (xVel < 0) xVel += 1;
		yVel -= 1;

		if (y > maxY) maxY = y;

		if (x > MAX_X) return -1;
		if (y < MIN_Y) return -1;

		if (x <= MAX_X && x >= MIN_X && y <= MAX_Y && y >= MIN_Y) return maxY;
	}
}