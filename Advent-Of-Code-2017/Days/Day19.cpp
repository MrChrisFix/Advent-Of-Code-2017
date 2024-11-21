#include "../general.h"

bool isLetter(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

string Day19_Part1(stringstream& input)
{
	vector<string> maze;

	while (!input.eof())
	{
		string line;
		getline(input, line);

		if (line.empty())
			break;
		maze.push_back(line);
	}
	string word = "";
	int x, y = 0;
	x = maze[0].find('|');

	char now, pipe = '|';
	int dir = 1;

	while (true)
	{
		now = maze[y][x];

		if (now == '+')
		{
			pipe = pipe == '|' ? '-' : '|';

			if (pipe == '-')
			{
				if (x - 1 >= 0 && maze[y][x - 1] == pipe || isLetter(maze[y][x - 1]))
					dir = -1;
				else if (x + 1 < maze[y].size() && maze[y][x + 1] == pipe || isLetter(maze[y][x + 1]))
					dir = 1;
			}
			else
			{
				if (y - 1 >= 0 && maze[y - 1][x] == pipe || isLetter(maze[y - 1][x]))
					dir = -1;
				else if (y + 1 < maze.size() && maze[y + 1][x] == pipe || isLetter(maze[y + 1][x]))
					dir = 1;
			}
		}
		else if (now == ' ')
		{
			break;
		}
		else if (isLetter(now))
		{
			word += now;
		}

		if (pipe == '|')
		{
			y += dir;
		}
		else
			x += dir;
	}

	return word;
}

int Day19_Part2(stringstream& input)
{
	vector<string> maze;

	while (!input.eof())
	{
		string line;
		getline(input, line);

		if (line.empty())
			break;
		maze.push_back(line);
	}
	int x, y = 0;
	x = maze[0].find('|');

	char now, pipe = '|';
	int dir = 1;

	int steps = 0;

	while (true)
	{
		now = maze[y][x];

		if (now == '+')
		{
			pipe = pipe == '|' ? '-' : '|';

			if (pipe == '-')
			{
				if (x - 1 >= 0 && maze[y][x - 1] == pipe || isLetter(maze[y][x - 1]))
					dir = -1;
				else if (x + 1 < maze[y].size() && maze[y][x + 1] == pipe || isLetter(maze[y][x + 1]))
					dir = 1;
			}
			else
			{
				if (y - 1 >= 0 && maze[y - 1][x] == pipe || isLetter(maze[y - 1][x]))
					dir = -1;
				else if (y + 1 < maze.size() && maze[y + 1][x] == pipe || isLetter(maze[y + 1][x]))
					dir = 1;
			}
		}
		else if (now == ' ')
		{
			break;
		}
		else if (isLetter(now))
		{
			//word += now;
		}

		if (pipe == '|')
		{
			y += dir;
		}
		else
			x += dir;

		steps++;
	}

	return steps;
}


void Day19(stringstream& input)
{
	cout << "Part 1 result is: " << Day19_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day19_Part2(input) << endl << endl;

	return;
}