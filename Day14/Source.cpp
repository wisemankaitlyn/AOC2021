// Day 14
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include<list>

using namespace std;

struct Rule
{
	char e1, e2, res;
};

struct Pair
{
	char e1, e2;
	long long LastNum = 0;
	long long NextNum = 0;
};

void main()
{
	vector<char> polymer;
	vector<Rule*> rules;
	vector<Pair*> pairs;
	vector<long long> counts(26, 0);

	ifstream in;
	in.open("input.txt");

	// get polymer
	{
		string temp;
		in >> temp;

		for (auto c : temp)
		{
			polymer.push_back(c);
		}
	}

	// get pairs
	for (int i = 0; i < polymer.size()-1; i++)
	{
		counts.at(int(polymer.at(i)) - 65)++;

		bool found = false;
		for (int j = 0; j < pairs.size(); j++)
		{
			if (polymer.at(i) == pairs.at(j)->e1)
			{
				if (polymer.at(i + 1) == pairs.at(j)->e2)
				{
					pairs.at(j)->LastNum++;
					found = true;
					break;
				}
			}
		}

		if (!found)
		{
			// create new pair
			Pair* tempPair = new Pair;
			tempPair->e1 = polymer.at(i);
			tempPair->e2 = polymer.at(i + 1);
			tempPair->LastNum = 1;

			pairs.push_back(tempPair);
		}
	}
	counts.at(int(polymer.at(polymer.size() - 1)) - 65)++;

	// get rules
	while (!in.eof())
	{
		char tempC;
		Rule* tempRule = new Rule;
		
		in >> tempRule->e1 >> tempRule->e2 >> tempC >> tempC >> tempRule->res;

		rules.push_back(tempRule);
	}
	rules.pop_back();
	in.close();

	for (int i = 0; i < 40; i++)
	{
		// for each pair with LastNum > 0, find out if a rule applies
		int numPairs = pairs.size();

		for (int pairIndex = 0; pairIndex < numPairs; pairIndex++)
		//for (auto p : pairs)
		{
			auto p = pairs.at(pairIndex);

			if (p->LastNum == 0) continue;

			bool ruleFound = false;
			for (auto r : rules)
			{
				if (p->e1 == r->e1 && p->e2 == r->e2)
				{
					// we have a matching rule
					ruleFound = true;

					counts.at(int(r->res) - 65) += p->LastNum;

					// find a pair for e1 and res
					{
						bool pairFound = false;
						
						for (auto pair : pairs)
						{
							if (pair->e1 == p->e1 && pair->e2 == r->res)
							{
								pairFound = true;
								pair->NextNum += p->LastNum;
								break;
							}
						}

						if (!pairFound)
						{
							Pair* tempPair = new Pair;
							tempPair->e1 = p->e1;
							tempPair->e2 = r->res;
							tempPair->LastNum = 0;
							tempPair->NextNum = p->LastNum;

							pairs.push_back(tempPair);
						}
					}

					// find a pair for e2 and res
					{
						bool pairFound = false;

						for (auto pair : pairs)
						{
							if (pair->e1 == r->res && pair->e2 == p->e2)
							{
								pairFound = true;
								pair->NextNum += p->LastNum;
								break;
							}
						}

						if (!pairFound)
						{
							Pair* tempPair = new Pair;
							tempPair->e1 = r->res;
							tempPair->e2 = p->e2;
							tempPair->LastNum = 0;
							tempPair->NextNum = p->LastNum;

							pairs.push_back(tempPair);
						}
					}
				}
			}

			if (!ruleFound)
			{
				p->NextNum += p->LastNum;
			}
		}

		for (auto p : pairs)
		{
			p->LastNum = p->NextNum;
			p->NextNum = 0;
		}

		/*if (i < 2)
		{
			for (auto p : pairs)
			{
				cout << p->e1 << p->e2 << ": " << p->LastNum << endl;
			}
			cout << endl;
		}*/
			
	}

	
	//for (int i = 0; i < 40; i++)
	//{
	//	auto it = polymer.begin();
	//	it++;
	//	for (; it != polymer.end(); it++)
	//	{
	//		for (auto r : rules)
	//		{
	//			if (r->e2 == *it)
	//			{
	//				it--;
	//				if (r->e1 == *(it))
	//				{
	//					// we've found an applicable rule
	//					it++;
	//					polymer.insert(it, r->res);
	//					break;
	//				}
	//				else it++;
	//			}
	//		}
	//	}
	//}

	/*vector<long long> counts(26, 0);

	for (auto c : polymer)
	{
		counts.at(int(c) - 65)++;
	}*/

	long long largest = 0;
	long long smallest = 10000000000000000;

	for (auto val : counts)
	{
		if (val > largest) largest = val;
		if (val < smallest && val != 0) smallest = val;
	}

	cout << "the largest minus the smallest is " << largest - smallest << endl;

	return;
}