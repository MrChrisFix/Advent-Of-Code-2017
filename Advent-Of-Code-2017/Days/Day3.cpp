#include "../general.h"

int Day3_Part1(stringstream& input)
{
	int n = stoi(input.str());

	int square = 1;

	while (square * square < n)
	{
		square += 2;
	}

	size_t squared = square * square;

	size_t ringSize = squared - (square - 2) * (square - 2);
	int side = ringSize / 4;

	size_t dist = 0;

	if (squared - side < n)
	{
		long long middle = squared - side / 2;
		dist = std::abs(middle - n);

	}
	else if (squared - 2 * side < n)
	{
		long long middle = squared - side / 2 - side;
		dist = std::abs(middle - n);
	}
	else if (squared - 3 * side < n)
	{
		long long middle = squared - side / 2 - 2 * side;
		dist = std::abs(middle - n);
	}
	else
	{
		long long middle = squared - side / 2 - 3 * side;
		dist = std::abs(middle - n);
	}


	return square / 2 + dist;
}

size_t Day3_Part2(stringstream& input)
{
	int n = stoi(input.str());

	const int SIZE = 15;

	std::vector<std::vector<size_t>> matrix(SIZE, std::vector<size_t>(SIZE, 0));

	const int MIDDLE = SIZE / 2 + 1;

	matrix[MIDDLE][MIDDLE] = 1;

	int x = MIDDLE, y = MIDDLE;

	int dir = 0; //0 - right, 1 - up, 2 - left, 3 - down

	for (int i = 1; ; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < i; k++)
			{
				if (dir == 0)
				{
					x++;
				}
				else if (dir == 1)
				{
					y--;
				}
				else if (dir == 2)
				{
					x--;
				}
				else if (dir == 3)
				{
					y++;
				}
				matrix[x][y] = matrix[x + 1][y] + matrix[x + 1][y - 1] + matrix[x][y - 1] + matrix[x - 1][y - 1] + matrix[x - 1][y] + matrix[x - 1][y + 1] + matrix[x][y + 1] + matrix[x + 1][y + 1];

				if (matrix[x][y] > n)
					return matrix[x][y];
			}
			dir = (dir + 1) % 4;
		}
	}

	return -1;
}


void Day3(stringstream& input)
{
	cout << "Part 1 result is: " << Day3_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day3_Part2(input) << endl << endl;

	return;
}