// Day 10
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>
#include<deque>
#include<algorithm>

using namespace std;

void main()
{
	vector<string> navSub;

	ifstream in;
	in.open("input.txt");

	string temp;
	in >> temp;
	while (!in.eof())
	{
		navSub.push_back(temp);
		in >> temp;
	}
	navSub.push_back(temp);
	in.close();

	long long score = 0;

	for (auto l : navSub)
	{
		std::deque<char> d;
		for (int i = 0; i < l.size(); i++)
		{
			if (l.at(i) == '(' || l.at(i) == '[' || l.at(i) == '{' || l.at(i) == '<')
			{
				d.push_back(l.at(i));
				continue;
			}

			bool incorrect = false;

			switch (d.back())
			{
			case '(':
				if (l.at(i) == ')') d.pop_back();
				else incorrect = true;
				break;
			case '[':
				if (l.at(i) == ']') d.pop_back();
				else incorrect = true;
				break;
			case '{':
				if (l.at(i) == '}') d.pop_back();
				else incorrect = true;
				break;
			case '<':
				if (l.at(i) == '>') d.pop_back();
				else incorrect = true;
				break;
			default:
				break;
			}

			if (incorrect)
			{
				switch (l.at(i))
				{
				case ')':
					score += 3;
					break;
				case ']':
					score += 57;
					break;
				case '}':
					score += 1197;
					break;
				case '>':
					score += 25137;
					break;
				}

				break;
			}
		}
	}

	cout << "part 1: the total syntax error score is " << score << endl;

	score = 0;
	vector<long long> s;

	for (auto l : navSub)
	{
		std::deque<char> d;
		bool incorrect = false;
		for (int i = 0; i < l.size(); i++)
		{
			if (l.at(i) == '(' || l.at(i) == '[' || l.at(i) == '{' || l.at(i) == '<')
			{
				d.push_back(l.at(i));
				continue;
			}

			switch (d.back())
			{
			case '(':
				if (l.at(i) == ')') d.pop_back();
				else incorrect = true;
				break;
			case '[':
				if (l.at(i) == ']') d.pop_back();
				else incorrect = true;
				break;
			case '{':
				if (l.at(i) == '}') d.pop_back();
				else incorrect = true;
				break;
			case '<':
				if (l.at(i) == '>') d.pop_back();
				else incorrect = true;
				break;
			default:
				break;
			}

			if (incorrect)
			{
				break;
			}
		}

		if (!incorrect)
		{
			score = 0;
			while (!d.empty())
			{
				score *= 5;
				switch (d.back())
				{
				case '(':
					score += 1;
					break;
				case '[':
					score += 2;
					break;
				case '{':
					score += 3;
					break;
				case '<':
					score += 4;
					break;
				}

				d.pop_back();
			}

			s.push_back(score);
		}
	}

	sort(s.begin(), s.end());

	cout << "part 2: the middle score is " << s.at(s.size() / 2) << endl;
}