#include "../general.h"
#include <set>

int Day22_Part1(stringstream& input)
{
	set<pair<long long, long long>> infected;

	int sideSide = sqrt(input.str().size());
	input.seekg(0);

	int y = -sideSide / 2;
	while (!input.eof())
	{
		string line;
		getline(input, line);

		int x = -sideSide / 2;
		for (int i = 0; i < line.size(); i++, x++)
		{
			if (line[i] == '#')
				infected.insert({ x, y });
		}
		y++;
	}

	int X = 0, Y = 0;
	int dir = 0; //0 Up, 1 Left, 2 Down, 3 Right

	int infections = 0;

	for (int i = 0; i < 10000; i++)
	{
		if (infected.contains({ X,Y }))
		{
			dir = (dir + 3) % 4;
			infected.erase({ X,Y });
		}
		else
		{
			dir = (dir + 1) % 4;
			infected.insert({ X,Y });
			infections++;
		}

		if (dir % 2 == 0)
		{
			Y += dir - 1;
		}
		else
		{
			X += dir - 2;
		}

	}

	return infections;
}

int Day22_Part2(stringstream& input)
{
	set<pair<long long, long long>> infected;
	set<pair<long long, long long>> weakened;
	set<pair<long long, long long>> flagged;

	int sideSide = sqrt(input.str().size());
	input.seekg(0);

	int y = -sideSide / 2;
	while (!input.eof())
	{
		string line;
		getline(input, line);

		int x = -sideSide / 2;
		for (int i = 0; i < line.size(); i++, x++)
		{
			if (line[i] == '#')
				infected.insert({ x, y });
		}
		y++;
	}

	int X = 0, Y = 0;
	int dir = 0; //0 Up, 1 Left, 2 Down, 3 Right

	int infections = 0;

	for (int i = 0; i < 10000000; i++)
	{
		if (infected.contains({ X,Y }))
		{
			dir = (dir + 3) % 4;

			flagged.insert({ X,Y });
			infected.erase({ X,Y });
		}
		else if (weakened.contains({ X,Y }))
		{
			infected.insert({ X,Y });
			weakened.erase({ X,Y });
			infections++;
		}
		else if (flagged.contains({ X,Y }))
		{
			dir = (dir + 2) % 4;
			flagged.erase({ X,Y });
		}
		else
		{
			dir = (dir + 1) % 4;
			weakened.insert({ X,Y });
		}

		if (dir % 2 == 0)
		{
			Y += dir - 1;
		}
		else
		{
			X += dir - 2;
		}

	}

	return infections;
}


void Day22(stringstream& input)
{
	cout << "Part 1 result is: " << Day22_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day22_Part2(input) << endl << endl;

	return;
}