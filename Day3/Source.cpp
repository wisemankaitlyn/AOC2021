// Day 3
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

void main()
{
	ifstream in;
	in.open("testinput2.txt");
	const int numBits = 12;
	const int numNums = 1000;

	char numbers[numBits][numNums];
	int gamma = 0;
	int epsilon = 0;

	char temp;
	
	int bitIndex = 0;
	int numIndex = 0;

	int colOnes[numBits] = { 0 };

	while (!in.eof())
	{
		in >> temp;
		if (temp == '1' || temp == '0')
		{
			numbers[bitIndex][numIndex] = temp;

			if (temp == '1')
			{
				colOnes[bitIndex]++;
			}

			bitIndex++;
			if (bitIndex >= numBits)
			{
				bitIndex = 0;
				numIndex++;
			}
		}
	}
	in.close();

	for (int i = 0; i < numBits; i++)
	{
		if (colOnes[i] > numNums / 2)
		{
			gamma += pow(2, numBits - i - 1);
		}
		else
		{
			epsilon += pow(2, numBits - i - 1);
		}
	}

	cout << "part 1: the power consumption is " << epsilon * gamma << endl;

	// part 2: oxy gen
	vector<int> oxygenGeneratorRating;
	vector<int> co2ScrubberRating;
	int OGR, CSR;

	for (int i = 0; i < numNums; i++)
	{
		oxygenGeneratorRating.push_back(i);
		co2ScrubberRating.push_back(i);
	}

	for (int bitInd = 0; bitInd < numBits; bitInd++)
	{
		int numOnesInRound = 0;
		// figure out most common bit in column
		for (auto index : oxygenGeneratorRating)
		{
			if (numbers[bitInd][index] == '1') numOnesInRound++;
		}

		// store indexes of values that don't match that most common bit
		vector<int> toRemove;

		if (numOnesInRound >= oxygenGeneratorRating.size()/2.0)
		{
			for (auto index : oxygenGeneratorRating)
			{
				if (numbers[bitInd][index] == '0') toRemove.push_back(index);
			}
		}
		else
		{
			for (auto index : oxygenGeneratorRating)
			{
				if (numbers[bitInd][index] == '1') toRemove.push_back(index);
			}
		}

		// remove the stored indexes from the vector
		for (auto index : toRemove)
		{
			oxygenGeneratorRating.erase(find(oxygenGeneratorRating.begin(), oxygenGeneratorRating.end(), index));
		}

		// break out if size == 1
		if (oxygenGeneratorRating.size() == 1) break;
	}

	OGR = 0;
	for (int i = 0; i < numBits; i++)
	{
		if (numbers[i][oxygenGeneratorRating.at(0)] == '1')
			OGR += pow(2, numBits - i - 1);
	}

	// co2
	for (int bitInd = 0; bitInd < numBits; bitInd++)
	{
		int numZerosInRound = 0;
		// figure out most common bit in column
		for (auto index : co2ScrubberRating)
		{
			if (numbers[bitInd][index] == '0') numZerosInRound++;
		}

		// store indexes of values that match that most common bit
		vector<int> toRemove;

		if (numZerosInRound <= co2ScrubberRating.size()/2.0)
		{
			for (auto index : co2ScrubberRating)
			{
				if (numbers[bitInd][index] == '1') toRemove.push_back(index);
			}
		}
		else
		{
			for (auto index : co2ScrubberRating)
			{
				if (numbers[bitInd][index] == '0') toRemove.push_back(index);
			}
		}

		// remove the stored indexes from the vector
		for (auto index : toRemove)
		{
			co2ScrubberRating.erase(find(co2ScrubberRating.begin(), co2ScrubberRating.end(), index));
		}

		// break out if size == 1
		if (co2ScrubberRating.size() == 1) break;
	}

	CSR = 0;
	for (int i = 0; i < numBits; i++)
	{
		if (numbers[i][co2ScrubberRating.at(0)] == '1')
			CSR += pow(2, numBits - i - 1);
	}

	cout << "part 2: the life support rating of the sub is " << OGR * CSR << endl;

	return;
}