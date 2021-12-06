// Day 6
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

struct fishBucket
{
	char fishTime;
	long long numFish = 0;
};

void main()
{
	ifstream in;
	in.open("input.txt");

	vector<char> fish;
	vector<fishBucket*> buckets;
	vector<fishBucket*> lastBuckets;

	int temp;
	char comma;

	in >> temp >> comma;
	while (!in.eof())
	{
		fish.push_back(temp);
		in >> temp >> comma;
	}
	fish.push_back(temp);
	in.close();

	for (int i = 0; i < 9; i++)
	{
		fishBucket* b = new fishBucket;
		b->fishTime = i;
		buckets.push_back(b);
	}

	for (auto f : fish)
	{
		buckets.at(f)->numFish++;
	}

	for (int day = 0; day < 256; day++)
	{
		long long num[9] = { 0 };
		for (int i = 0; i < 9; i++)
		{
			num[i] = buckets.at(i)->numFish;
		}

		buckets.at(0)->numFish = num[1];
		buckets.at(1)->numFish = num[2];
		buckets.at(2)->numFish = num[3];
		buckets.at(3)->numFish = num[4];
		buckets.at(4)->numFish = num[5];
		buckets.at(5)->numFish = num[6];
		buckets.at(6)->numFish = num[7] + num[0];
		buckets.at(7)->numFish = num[8];
		buckets.at(8)->numFish = num[0];
	}

	long long s = 0;
	for (int i = 0; i < 9; i++)
	{
		s += buckets.at(i)->numFish;
	}

	cout << "part 2: the number of fish after 256 days would be " << s << endl;

	return;
}