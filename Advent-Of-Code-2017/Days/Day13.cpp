#include "../general.h"
#include <map>

int scannerPos(int picosecond, int range)
{
	return picosecond % ((range-1)*2);
}


int Day13_Part1(stringstream& input)
{
	int picosecond = 0;
	int severity = 0;
	while (!input.eof())
	{
		int layer, range;
		char trash;
		input >> layer >> trash >> range;

		while (layer != picosecond)
			picosecond++;

		int scanner = scannerPos(picosecond, range);

		if (scanner == 0)
		{
			severity += layer * range;
		}

		picosecond++;
	}

	return severity;
}

int Day13_Part2(stringstream& input)
{
	std::map<int, int> ranges;

	
	while (!input.eof())
	{
		int layer, range;
		char trash;
		input >> layer >> trash >> range;

		ranges[layer] = range;
	}

	int delay = 0;
	for (;; delay++)
	{
		bool fail = false;
		int picosecond = delay;
		int severity = 0;
		int layer = 0;
		for (auto& el : ranges)
		{
			while (el.first != layer)
			{
				picosecond++;
				layer++;
			}

			if (scannerPos(picosecond, el.second) == 0)
			{
				fail = true;
				break; 
			}
			picosecond++;
			layer++;
		}
		if (!fail)
			break;
	}

	return delay;
}


void Day13(stringstream& input)
{
	cout<<"Part 1 result is: " << Day13_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day13_Part2(input)<<endl<<endl;

	return;
}