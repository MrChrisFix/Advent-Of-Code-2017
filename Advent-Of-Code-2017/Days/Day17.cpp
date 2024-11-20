#include "../general.h"

int Day17_Part1(stringstream& input)
{
	std::vector<int> spin = { 0 };

	int steps = stoi(input.str());

	int curPos = 0;
	for (int i = 0; i < 2017; i++)
	{
		curPos = (curPos + steps) % spin.size();
		spin.insert(spin.begin() + curPos+1, i + 1);
		curPos++;
	}

	return spin[(curPos+1)%spin.size()];
}

int Day17_Part2(stringstream& input)
{
	std::vector<int> spin = { 0 };

	int steps = stoi(input.str());

	int curPos = 0;
	int secondValue = 0;

	for (int i = 0; i < 50000000; i++)
	{
		curPos = (curPos + steps) % (i+1);
		if (curPos == 0)
			secondValue = i + 1;
		curPos++;
	}

	return secondValue;
}


void Day17(stringstream& input)
{
	cout<<"Part 1 result is: " << Day17_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day17_Part2(input)<<endl<<endl;

	return;
}