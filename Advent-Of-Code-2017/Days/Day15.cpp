#include "../general.h"

int Day15_Part1(stringstream& input)
{
	size_t prevGenA = 0, prevGenB = 0;
	std::string trash;
	input >> trash >> trash >> trash >> trash >> prevGenA;
	input >> trash >> trash >> trash >> trash >> prevGenB;

	int cnt = 0;

	for (size_t round = 0; round < 40000000; round++)
	{
		prevGenA = (prevGenA * 16807) % 2147483647;
		prevGenB = (prevGenB * 48271) % 2147483647;

		if (prevGenA % 65536 == prevGenB % 65536)
			cnt++;
	}


	return cnt;
}

int Day15_Part2(stringstream& input)
{
	size_t prevGenA = 0, prevGenB = 0;
	std::string trash;
	input >> trash >> trash >> trash >> trash >> prevGenA;
	input >> trash >> trash >> trash >> trash >> prevGenB;

	int cnt = 0;

	for (size_t round = 0; round < 5000000; round++)
	{
		do
		{
			prevGenA = (prevGenA * 16807) % 2147483647;

		} while (prevGenA % 4 != 0);

		do
		{
			prevGenB = (prevGenB * 48271) % 2147483647;
		} while (prevGenB % 8 != 0);

		if (prevGenA % 65536 == prevGenB % 65536)
			cnt++;
	}


	return cnt;
}

void Day15(stringstream& input)
{
	cout << "Part 1 result is: " << Day15_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day15_Part2(input) << endl << endl;

	return;
}