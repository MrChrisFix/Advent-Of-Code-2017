#include "../general.h"
#include <numeric>
#include <format>
#include <set>

std::string KnotHash(std::string chars)
{
	int curPos = 0, skipSize = 0;
	std::vector<uint8_t> lengths;
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

std::vector<std::string> createGrid(std::string key)
{
	std::vector<std::string> grid;

	std::string mapping['f' + 1];
	mapping['0'] = "0000";
	mapping['1'] = "0001";
	mapping['2'] = "0010";
	mapping['3'] = "0011";
	mapping['4'] = "0100";
	mapping['5'] = "0101";
	mapping['6'] = "0110";
	mapping['7'] = "0111";
	mapping['8'] = "1000";
	mapping['9'] = "1001";
	mapping['a'] = "1010";
	mapping['b'] = "1011";
	mapping['c'] = "1100";
	mapping['d'] = "1101";
	mapping['e'] = "1110";
	mapping['f'] = "1111";

	for (int i = 0; i < 128; i++)
	{
		std::string hash = KnotHash(key + "-" + std::to_string(i));
		std::string binary = "";
		for (int j = 0; j < 32; j++)
		{
			binary += mapping[hash[j]];
		}
		grid.push_back(binary);
	}

	return grid;
}

void flood_visit(std::vector<std::string>& grid, std::set<std::pair<int, int>>& visited, int xx, int yy)
{
	if (visited.contains({ yy,xx }) || grid[yy][xx] == '0')
		return;

	visited.insert({ yy,xx });

	if (yy - 1 >= 0)
	{
		flood_visit(grid, visited, xx, yy - 1);
	}
	if (yy + 1 < 128)
	{
		flood_visit(grid, visited, xx, yy + 1);
	}
	if (xx - 1 >= 0)
	{
		flood_visit(grid, visited, xx - 1, yy);
	}
	if (xx + 1 < 128)
	{
		flood_visit(grid, visited, xx + 1, yy);
	}
}

int Day14_Part1(stringstream& input)
{
	std::string key = input.str();

	auto grid = createGrid(key);

	int squares = 0;
	for (int i = 0; i < 128; i++)
	{
		squares += std::count_if(grid[i].begin(), grid[i].end(), [](char& c) { return c == '1'; });
	}

	return squares;
}

int Day14_Part2(stringstream& input)
{
	std::string key = input.str();
	std::vector<std::string> grid = createGrid(key);

	int regions = 0;
	std::set<std::pair<int, int>> visited;

	for (int y = 0; y < 128; y++)
	{
		for (int x = 0; x < 128; x++)
		{
			if (grid[y][x] == '0')
				continue;

			if (visited.contains({ y,x }))
				continue;

			regions++;

			flood_visit(grid, visited, x, y);
		}
	}

	return regions;
}


void Day14(stringstream& input)
{
	cout << "Part 1 result is: " << Day14_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day14_Part2(input) << endl << endl;

	return;
}