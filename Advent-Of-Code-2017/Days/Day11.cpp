#include "../general.h"
#include <algorithm>
#include <string>



void equalize(int& left, int& middle, int& right)
{
	if (left > right)
	{
		middle += right;
		left -= right;
		right = 0;
	}
	else
	{
		middle += left;
		right -= left;
		left = 0;
	}

}

int calcSteps(int& s, int& se, int& ne, int& n, int& nw, int& sw)
{
	int zeros = (s == 0) + (n == 0) + (se == 0) + (sw == 0) + (ne == 0) + (nw == 0);

	do
	{
		equalize(sw, s, se);
		equalize(s, se, ne);
		equalize(se, ne, n);
		equalize(ne, n, nw);
		equalize(n, nw, sw);
		equalize(nw, sw, s);

		zeros = (s == 0) + (n == 0) + (se == 0) + (sw == 0) + (ne == 0) + (nw == 0);
	} while (zeros < 4);

	return n + s + nw + ne + sw + se;

}


int Day11_Part1(stringstream& input)
{
	int s, se, ne, n, nw, sw;
	s = se = ne = n = nw = sw = 0;

	std::string all = input.str();
	std::replace(all.begin(), all.end(), ',', ' ');
	std::stringstream ss(all);

	while (!ss.eof())
	{
		std::string dir;
		ss >> dir;

		if (dir == "nw")
			nw++;
		else if (dir == "sw")
			sw++;
		else if (dir == "se")
			se++;
		else if (dir == "ne")
			ne++;
		else if (dir == "s")
			s++;
		else if (dir == "n")
			n++;
	}

	int sum = calcSteps(s, se, ne, n, nw, sw);

	return sum;
}

int Day11_Part2(stringstream& input)
{
	int s, se, ne, n, nw, sw;
	s = se = ne = n = nw = sw = 0;

	std::string all = input.str();
	std::replace(all.begin(), all.end(), ',', ' ');
	std::stringstream ss(all);

	int max = 0;

	while (!ss.eof())
	{
		std::string dir;
		ss >> dir;

		if (dir == "nw")
			nw++;
		else if (dir == "sw")
			sw++;
		else if (dir == "se")
			se++;
		else if (dir == "ne")
			ne++;
		else if (dir == "s")
			s++;
		else if (dir == "n")
			n++;

		int record = calcSteps(s, se, ne, n, nw, sw);

		if (record > max)
			max = record;
	}

	return max;
}


void Day11(stringstream& input)
{
	cout << "Part 1 result is: " << Day11_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day11_Part2(input) << endl << endl;

	return;
}