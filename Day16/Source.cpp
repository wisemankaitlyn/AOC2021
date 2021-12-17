// Day 16
// Advent of Code 2021
// Kaitlyn Wiseman

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include<bitset>

using namespace std;

std::vector<char>::iterator BITS(std::vector<char>::iterator startPos, long long* r);

vector<char> bin;
int versionSum = 0;

void main()
{
	// convert from hex to bin
	ifstream in;
	in.open("input.txt");

	while (!in.eof())
	{
		char temp;
		in >> temp;

		if (temp < 65)
			for (auto b : { 3, 2, 1, 0 })
				bin.push_back(bitset<4>(temp - 48)[b]);
		else
			for (auto b : { 3, 2, 1, 0 })
				bin.push_back(bitset<4>(temp - 55)[b]);
	}
	for (auto b : { 0, 1, 2, 3 }) bin.pop_back();
	in.close();

	long long* result = new long long;
	BITS(bin.begin(), result);

	cout << "The version sum is " << versionSum << endl;
	cout << "Evaluating the BITS transmission results in " << *result << endl;

	return;
}

std::vector<char>::iterator BITS(std::vector<char>::iterator startPos, long long* r)
{
	// get version
	bitset<3> version;
	version[2] = *startPos;
	version[1] = *(startPos + 1);
	version[0] = *(startPos + 2);
	int v = version.to_ulong();
	
	versionSum += v;

	// get type ID
	bitset<3> typeID;
	typeID[2] = *(startPos + 3);
	typeID[1] = *(startPos + 4);
	typeID[0] = *(startPos + 5);
	int t = typeID.to_ulong();

	if (t != 4)
	{
		int bitLength;
		std::vector<char>::iterator bitIt = startPos + 7;
		int subpacketLengthInt; 
		long long result;

		if (*(startPos + 6))
		{
			// length type ID = 1
			// next 11 bits are a number that represents the total
			// number in packets of the subpackets
			bitLength = 11;

			bitset<11> subpacketLengthBin;
			for (int i = 0; i < bitLength; i++)
			{
				subpacketLengthBin[10 - i] = *(bitIt + i);
			}
			subpacketLengthInt = subpacketLengthBin.to_ulong();

			bitIt += bitLength;

			int numPackets = 0;

			vector<long long> terms;

			switch (t)
			{
			case 0: // sum
				result = 0;

				do
				{
					long long* addend = new long long;
					bitIt = BITS(bitIt, addend);
					result += *addend;
					numPackets++;
				} while (numPackets < subpacketLengthInt);

				break;
			case 1: // product
				result = 1;

				do
				{
					long long* multiplicand = new long long;
					bitIt = BITS(bitIt, multiplicand);
					result *= *multiplicand;
					numPackets++;
				} while (numPackets < subpacketLengthInt);

				break;
			case 2: // minimum
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
					numPackets++;
				} while (numPackets < subpacketLengthInt);

				sort(terms.begin(), terms.end());

				result = terms.at(0);
				break;
			case 3: // maximum
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
					numPackets++;
				} while (numPackets < subpacketLengthInt);

				sort(terms.begin(), terms.end(), greater <>());

				result = terms.at(0);
				break;
			case 5: // greater than
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
					numPackets++;
				} while (numPackets < subpacketLengthInt);

				result = (terms.at(0) > terms.at(1));
				break;
			case 6: // less than
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
					numPackets++;
				} while (numPackets < subpacketLengthInt);

				result = (terms.at(0) < terms.at(1));
				break;
			case 7: // equal to
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
					numPackets++;
				} while (numPackets < subpacketLengthInt);

				result = (terms.at(0) == terms.at(1));
				break;
			}

			*r = result;
		}
		else
		{
			// length type ID = 0
			// next 15 bits are a number that represents the total
			// length in bits of the subpackets
			bitLength = 15;

			bitset<15> subpacketLengthBin;
			for (int i = 0; i < bitLength; i++)
			{
				subpacketLengthBin[14 - i] = *(bitIt + i);
			}
			subpacketLengthInt = subpacketLengthBin.to_ulong();

			bitIt += bitLength;

			std::vector<char>::iterator finalPos = bitIt + subpacketLengthInt;

			vector<long long> terms;

			switch (t)
			{
			case 0: // sum
				result = 0;

				do
				{
					long long* addend = new long long;
					bitIt = BITS(bitIt, addend);
					result += *addend;
				} while (bitIt < finalPos);

				break;
			case 1: // product
				result = 1;

				do
				{
					long long* multiplicand = new long long;
					bitIt = BITS(bitIt, multiplicand);
					result *= *multiplicand;
				} while (bitIt < finalPos);

				break;
			case 2: // minimum
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
				} while (bitIt < finalPos);

				sort(terms.begin(), terms.end());

				result = terms.at(0);
				break;
			case 3: // maximum
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
				} while (bitIt < finalPos);

				sort(terms.begin(), terms.end(), greater <>());

				result = terms.at(0);
				break;
			case 5: // greater than
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
				} while (bitIt < finalPos);

				result = (terms.at(0) > terms.at(1));
				break;
			case 6: // less than
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
				} while (bitIt < finalPos);

				result = (terms.at(0) < terms.at(1));
				break;
			case 7: // equal to
				do
				{
					long long* term = new long long;
					bitIt = BITS(bitIt, term);
					terms.push_back(*term);
				} while (bitIt < finalPos);

				result = (terms.at(0) == terms.at(1));
				break;
			}

			*r = result;
		}

		return bitIt;
	}
	else
	{
		// type ID 4 represents a literal value
		vector<long long> values;
		std::vector<char>::iterator pos = startPos + 6;
		//int bitCnt = 0;

		//while (*pos != 1) pos++;

		do
		{
			bitset<4> valueBin;
			valueBin[3] = *(pos + 1);
			valueBin[2] = *(pos + 2);
			valueBin[1] = *(pos + 3);
			valueBin[0] = *(pos + 4);
			int valueInt = valueBin.to_ulong();
			values.emplace(values.begin(), valueInt);

			pos = pos + 5;
		} while (*(pos - 5) == 1);

		long long result = 0;
		for (int i = 0; i < values.size(); i++)
		{
			result += values.at(i) * pow(16, i);
		}

		*r = result;

		return pos;

	}

	return startPos;
}