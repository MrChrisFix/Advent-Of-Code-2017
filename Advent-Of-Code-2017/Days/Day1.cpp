#include "../general.h"

int Day1_Part1(stringstream& input)
{
	std::string in = input.str();

	int sum = 0;

	for (int i = 1; i < in.size(); i++)
	{
		if (in[i - 1] == in[i])
		{
			sum += in[i] - '0';
		}
	}
	if(in[0] == in[in.size() -1])
		sum += in[in.size() - 1] - '0';

	return sum;
}

int Day1_Part2(stringstream& input)
{
	std::string in = input.str();

	int sum = 0;
	const int half = in.size()/2;

	for (int i = 0; i < in.size(); i++)
	{
		int latter = (i + half) % in.size();

		if (in[i] == in[latter])
		{
			sum += in[i] - '0';
		}
	}

	return sum; //1240 too high
}


void Day1(stringstream& input)
{
	cout<<"Part 1 result is: " << Day1_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day1_Part2(input)<<endl<<endl;

	return;
}