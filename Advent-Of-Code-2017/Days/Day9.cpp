#include "../general.h"

int Day9_Part1(stringstream& input)
{
	std::string stream = input.str();
	int score = 0;

	int nestLevel = 0;
	bool garbage = false;

	for (size_t i = 0; i < stream.size(); i++)
	{
		char newChar = stream[i];
		if (newChar == '!')
		{
			i++;
			continue;
		}
		else if (newChar == '{' && !garbage)
		{
			nestLevel++;
		}
		else if (newChar == '}' && !garbage)
		{
			score += nestLevel;
			nestLevel--;
		}
		else if (newChar == '<' && !garbage)
		{
			garbage = true;
		}
		else if (newChar == '>')
		{
			garbage = false;
		}
	}

	return score;
}

int Day9_Part2(stringstream& input)
{
	std::string stream = input.str();

	bool garbage = false;
	int garbageCnt = 0;

	for (size_t i = 0; i < stream.size(); i++)
	{
		char newChar = stream[i];
		if (newChar == '!')
		{
			i++;
			continue;
		}
		else if (newChar == '<' && !garbage)
		{
			garbage = true;
		}
		else if (newChar == '>')
		{
			garbage = false;
		}
		else if(garbage)
		{
			garbageCnt++;
		}
	}

	return garbageCnt;
}


void Day9(stringstream& input)
{
	cout<<"Part 1 result is: " << Day9_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day9_Part2(input)<<endl<<endl;

	return;
}