#include "../general.h"
#include <set>

int Day6_Part1(stringstream& input)
{
	std::vector<int> banks;

	while (!input.eof())
	{
		int num;
		input >> num;
		banks.push_back(num);
	}

	std::set< std::vector<int>> apperences;
	int steps = 1;

	while (true)
	{
		auto it = std::max_element(banks.begin(), banks.end());

		int index = std::distance(banks.begin(), it);
		int value = *it;
		banks[index] = 0;

		while (value > 0)
		{
			index = (index + 1) % banks.size();

			banks[index]++;
			value--;
		}
		if (apperences.contains(banks))
			break;

		apperences.insert(banks);
		steps++;
	}
	
	return steps;
}

int Day6_Part2(stringstream& input)
{
	std::vector<int> banks;

	while (!input.eof())
	{
		int num;
		input >> num;
		banks.push_back(num);
	}

	std::set< std::vector<int>> apperences;
	int steps = 1;

	std::vector<int> special;

	while (true)
	{
		auto it = std::max_element(banks.begin(), banks.end());

		int index = std::distance(banks.begin(), it);
		int value = *it;
		banks[index] = 0;

		while (value > 0)
		{
			index = (index + 1) % banks.size();

			banks[index]++;
			value--;
		}
		if (apperences.contains(banks))
		{
			special = banks;
			break;
		}

		apperences.insert(banks);
	}
	while (true)
	{
		auto it = std::max_element(banks.begin(), banks.end());

		int index = std::distance(banks.begin(), it);
		int value = *it;
		banks[index] = 0;

		while (value > 0)
		{
			index = (index + 1) % banks.size();

			banks[index]++;
			value--;
		}
		if (banks == special)
		{
			break;
		}
		steps++;
	}

	return steps;
}


void Day6(stringstream& input)
{
	cout<<"Part 1 result is: " << Day6_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day6_Part2(input)<<endl<<endl;

	return;
}