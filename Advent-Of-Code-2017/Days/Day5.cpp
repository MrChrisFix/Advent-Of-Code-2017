#include "../general.h"

int Day5_Part1(stringstream& input)
{
	std::vector<int> nums;
	while (!input.eof())
	{
		int num;
		input >> num;
		nums.push_back(num);
	}

	int steps = 0;

	int curPos = 0;
	while (curPos < nums.size() && curPos >= 0)
	{
		int jump = nums[curPos];
		nums[curPos]++;
		curPos += jump;
		steps++;
	}

	return steps;
}

int Day5_Part2(stringstream& input)
{
	std::vector<int> nums;
	while (!input.eof())
	{
		int num;
		input >> num;
		nums.push_back(num);
	}

	int steps = 0;

	int curPos = 0;
	while (curPos < nums.size() && curPos >= 0)
	{
		int jump = nums[curPos];
		if (jump >= 3)
			nums[curPos]--;
		else
			nums[curPos]++;
		curPos += jump;
		steps++;
	}

	return steps;
}


void Day5(stringstream& input)
{
	cout<<"Part 1 result is: " << Day5_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day5_Part2(input)<<endl<<endl;

	return;
}