// Day 8
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

struct display
{
	vector<string> d{" ", " ", " ", " "};
};

struct signalSet
{
	vector<string> s;
};

void main()
{
	vector<display*> displays;
	vector<signalSet*> signals;

	ifstream in;
	in.open("input.txt");

	string s;
	signalSet* tempSS = new signalSet;
	
	in >> s;
	while (!in.eof())
	{
		if (s == "|")
		{
			signals.push_back(tempSS);
			tempSS = new signalSet;

			display* temp = new display;
			in >> s;
			temp->d.at(0) = s;
			in >> s;
			temp->d.at(1) = s;
			in >> s;
			temp->d.at(2) = s;
			in >> s;
			temp->d.at(3) = s;

			displays.push_back(temp);
		}
		else
		{
			tempSS->s.push_back(s);
		}

		in >> s;
	}
	in.close();

	int numTimes = 0;
	for (auto dis : displays)
	{
		for (int i = 0; i < 4; i++)
		{
			if (dis->d.at(i).size() == 2 || dis->d.at(i).size() == 4 || dis->d.at(i).size() == 3 || dis->d.at(i).size() == 7)
				numTimes++;
		}
	}

	cout << "part 1: the number of times a 1, 4, 7, or 8 is " << numTimes << endl;

	int sum = 0;
	vector<char> sigNames = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
	for (int ind = 0; ind < displays.size(); ind++)
	{
		char h, i, j, k, l, m, n;

		string zero, one, two, three, four, five, six, seven, eight, nine;

		for (auto sig : signals.at(ind)->s)
		{
			if      (sig.size() == 2) one   = sig;
			else if (sig.size() == 4) four  = sig;
			else if (sig.size() == 3) seven = sig;
			else if (sig.size() == 7) eight = sig;
		}

		// find h
		for (auto c : sigNames)
		{
			if (seven.find(c) != std::string::npos && eight.find(c) != std::string::npos && one.find(c) == std::string::npos && four.find(c) == std::string::npos)
			{
				h = c;
				break;
			}
		}

		for (auto c : sigNames)
		{
			int numTimesFound = 0;
			for (auto sig : signals.at(ind)->s)
			{
				if (sig.find(c) != std::string::npos)
				{
					numTimesFound++;
				}
			}

			if (numTimesFound == 4) l = c;
			else if (numTimesFound == 6) k = c;
			else if (numTimesFound == 9) n = c;
		}

		// we've found h, k, l, n
		// we need to find i, j, m

		// i is the one that one, four, seven, and eight have that is not n
		for (auto c : sigNames)
		{
			if (c != n && one.find(c) != std::string::npos && four.find(c) != std::string::npos && seven.find(c) != std::string::npos && eight.find(c) != std::string::npos)
			{
				i = c;
				break;
			}
		}

		// j is the one that four and eight have but one and seven don't that isn't k
		for (auto c : sigNames)
		{
			if (c != k && one.find(c) == std::string::npos && four.find(c) != std::string::npos && seven.find(c) == std::string::npos && eight.find(c) != std::string::npos)
			{
				j = c;
				break;
			}
		}

		// m is the one that eight has but one, four, and seven don't that isn't l
		for (auto c : sigNames)
		{
			if (c != l && one.find(c) == std::string::npos && four.find(c) == std::string::npos && seven.find(c) == std::string::npos && eight.find(c) != std::string::npos)
			{
				m = c;
				break;
			}
		}


		two = std::string() + h + i + j + l + m;
		three = std::string() + h + i + j + n + m;
		five = std::string() + h + k + j + n + m;
		six = std::string() + h + k + j + l + m + n;
		nine = std::string() + h + i + j + k + m + n;
		zero = std::string() + h + i + k + l + m + n;

		for (int dispNum = 0; dispNum < 4; dispNum++)
		{
			if (displays.at(ind)->d.at(dispNum).size() == zero.size())
			{
				bool eq = true;
				for (auto c : zero)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 0 * pow(10, 3 - dispNum);
			}
			if (displays.at(ind)->d.at(dispNum).size() == one.size())
			{
				bool eq = true;
				for (auto c : one)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 1 * pow(10, 3 - dispNum);
			}
			if (displays.at(ind)->d.at(dispNum).size() == two.size())
			{
				bool eq = true;
				for (auto c : two)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 2 * pow(10, 3 - dispNum);
			}
			if (displays.at(ind)->d.at(dispNum).size() == three.size())
			{
				bool eq = true;
				for (auto c : three)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 3 * pow(10, 3 - dispNum);
			}
			if (displays.at(ind)->d.at(dispNum).size() == four.size())
			{
				bool eq = true;
				for (auto c : four)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 4 * pow(10, 3 - dispNum);
			}
			if (displays.at(ind)->d.at(dispNum).size() == five.size())
			{
				bool eq = true;
				for (auto c : five)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 5 * pow(10, 3 - dispNum);
			}
			if (displays.at(ind)->d.at(dispNum).size() == six.size())
			{
				bool eq = true;
				for (auto c : six)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 6 * pow(10, 3 - dispNum);
			}
			if (displays.at(ind)->d.at(dispNum).size() == seven.size())
			{
				bool eq = true;
				for (auto c : seven)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 7 * pow(10, 3 - dispNum);
			}
			if (displays.at(ind)->d.at(dispNum).size() == eight.size())
			{
				bool eq = true;
				for (auto c : eight)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 8 * pow(10, 3 - dispNum);
			}
			if (displays.at(ind)->d.at(dispNum).size() == nine.size())
			{
				bool eq = true;
				for (auto c : nine)
				{
					if (displays.at(ind)->d.at(dispNum).find(c) == std::string::npos) eq = false;
				}

				if (eq) sum += 9 * pow(10, 3 - dispNum);
			}
		}
	}
	cout << "part 2: the sum of the displays is " << sum << endl;
}