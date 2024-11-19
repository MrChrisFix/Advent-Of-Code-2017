#include "../general.h"

int Day2_Part1(stringstream& input)
{
	int sum = 0;
	while (!input.eof())
	{
		std::string sline;
		getline(input, sline);
		stringstream line(sline);

		int min = -1, max = -1;
		while(!line.eof())
		{
			int num;
			line >> num;
			if (min == -1)
				min = max = num;
			
			if (min > num)
				min = num;

			if (max < num)
				max = num;
		}
		sum += max - min;
	}
	return sum;
}

int Day2_Part2(stringstream& input)
{
	int sum = 0;
	while (!input.eof())
	{
		std::string sline;
		getline(input, sline);
		stringstream line(sline);

		std::vector<int> nums;
		while (!line.eof())
		{
			int num;
			line >> num;
			nums.push_back(num);
		}

		for (int i = 0; i < nums.size(); i++)
		{
			for (int j = i + 1; j < nums.size(); j++)
			{
				if (nums[i]% nums[j] == 0)
				{
					sum += nums[i] / nums[j];
				}
				else if (nums[j] % nums[i] == 0)
				{
					sum += nums[j] / nums[i];
				}
			}
		}
	}
	return sum;
}


void Day2(stringstream& input)
{
	cout<<"Part 1 result is: " << Day2_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day2_Part2(input)<<endl<<endl;

	return;
}