// Day 12
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

struct Cave
{
	string name;
	bool big;
	vector<Cave*> adj;
};

int inCaves(string temp);
int numPaths(Cave* c, vector<string> path);
int numPaths2(Cave* c, vector<string> path);

vector<Cave*> caves;

void main()
{
	ifstream in;
	in.open("input.txt");

	Cave* tempCave = new Cave;
	string temp1, temp2;

	getline(in, temp1, '-');
	getline(in, temp2, '\n');

	while (!in.eof())
	{
		int index1 = inCaves(temp1);
		if (index1 == -1)
		{
			// create the node and set the index
			tempCave = new Cave;
			tempCave->name = temp1;
			tempCave->big  = isupper(temp1.at(0));

			caves.push_back(tempCave);
			index1 = caves.size() - 1;
		}

		int index2 = inCaves(temp2);
		if (index2 == -1)
		{
			// create the node and set the index
			tempCave = new Cave;
			tempCave->name = temp2;
			tempCave->big  = isupper(temp2.at(0));

			caves.push_back(tempCave);
			index2 = caves.size() - 1;
		}

		// connect the nodes
		caves.at(index1)->adj.push_back(caves.at(index2));
		caves.at(index2)->adj.push_back(caves.at(index1));

		getline(in, temp1, '-');
		getline(in, temp2, '\n');
	}
	in.close();
	vector<string> path;
	path.push_back("start");
	int p = numPaths(caves.at(0), path);

	cout << "part 1: the number of paths to end is " << p << endl;

	p = numPaths2(caves.at(0), path);

	cout << "part 2: the number of paths to end is " << p << endl;
}

int inCaves(string temp)
{
	for (int i = 0; i < caves.size(); i++)
	{
		if (caves.at(i)->name == temp) return i;
	}
	return -1;
}

int numPaths(Cave* c, vector<string> path)
{
	int num = 0;
	
	for (auto a : c->adj)
	{
		vector<string> newPath = path;
		if (a->name == "end")
		{
			num += 1;
			continue;
		}
		else if (!(a->big))
		{
			if (find(path.begin(), path.end(), a->name) != path.end())
			{
				continue;
			}
		}

		newPath.push_back(a->name);
		num += numPaths(a, newPath);
	}

	return num;
}

int numPaths2(Cave* c, vector<string> path)
{
	int num = 0;

	for (auto a : c->adj)
	{
		vector<string> newPath = path;
		if (a->name == "end")
		{
			num += 1;
			continue;
		}
		else if (a->name == "start")
		{
			continue;
		}
		else if (!(a->big))
		{
			// find out if we've gone once
			auto it = find(path.begin(), path.end(), a->name);
			if (it != path.end())
			{
				// we've gone at least once

				// figure out if any lowercase cave has gone twice
				bool done = false;
				for (int i = 1; i < path.size() && !done; i++)
				{
					if (!isupper(path.at(i).at(0)))
					{
						it = find(path.begin(), path.end(), path.at(i));
						done = (find(it + 1, path.end(), path.at(i)) != path.end());
					}
				}

				if (done) continue;
			}
		}

		newPath.push_back(a->name);
		num += numPaths2(a, newPath);
	}

	return num;
}