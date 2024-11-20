#include "../general.h"
#include <numeric>
#include <format>

int Day10_Part1(stringstream& input)
{
	if (input.peek() < '0' || input.peek() > '9')
		return -1;

	int curPos = 0, skipSize = 0;
	std::vector<int> lengths;

	while (!input.eof())
	{
		int num;
		char comma;
		input >> num >> comma;
		lengths.push_back(num);
	}

	const int TABLE_SIZE = 256;

	std::vector<int> table(TABLE_SIZE);
	std::iota(table.begin(), table.end(), 0);

	for (auto& len : lengths)
	{
		if (len > TABLE_SIZE)
			continue;

		if (curPos + len > table.size())
		{
			std::vector<int> temp(table.begin() + curPos, table.end());
			temp.insert(temp.end(), table.begin(), table.begin() + (len - (TABLE_SIZE - curPos)));
			std::reverse(temp.begin(), temp.end());

			std::copy(temp.begin(), temp.begin() + (TABLE_SIZE - curPos), table.begin() + curPos);
			std::copy(temp.begin() + (TABLE_SIZE - curPos), temp.end(), table.begin());
		}
		else
		{
			std::reverse(table.begin() + curPos, table.begin() + curPos + len);
		}

		curPos = (curPos + len + skipSize) % TABLE_SIZE;
		skipSize++;
	}


	return table[0] * table[1];
}

string Day10_Part2(stringstream& input)
{
	int curPos = 0, skipSize = 0;
	std::vector<uint8_t> lengths;

	std::string chars = input.str();

	for (auto& ch : chars)
	{
		lengths.push_back(ch);
	}
	lengths.insert(lengths.end(), { 17, 31, 73, 47, 23 });

	const int TABLE_SIZE = 256;

	std::vector<int> table(TABLE_SIZE);
	std::iota(table.begin(), table.end(), 0);

	for (int round = 0; round < 64; round++)
	{
		for (auto& len : lengths)
		{
		if (len > TABLE_SIZE)
			continue;

			if (curPos + len > table.size())
			{
				std::vector<int> temp(table.begin() + curPos, table.end());
				temp.insert(temp.end(), table.begin(), table.begin() + (len - (TABLE_SIZE - curPos)));
				std::reverse(temp.begin(), temp.end());

				std::copy(temp.begin(), temp.begin() + (TABLE_SIZE - curPos), table.begin() + curPos);
				std::copy(temp.begin() + (TABLE_SIZE - curPos), temp.end(), table.begin());
			}
			else
			{
				std::reverse(table.begin() + curPos, table.begin() + curPos + len);
			}
			curPos = (curPos + len + skipSize) % TABLE_SIZE;
			skipSize++;
		}
	}

	std::string result = "";
	for (int i = 0; i < 16; i++)
	{
		int num = table[i * 16];
		for (int j = 1; j < 16; j++)
		{
			num ^= table[i * 16 + j];
		}
		result += std::format("{:02x}", num);
	}

	return result;
}


void Day10(stringstream& input)
{
	cout << "Part 1 result is: " << Day10_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day10_Part2(input) << endl << endl;

	return;
}