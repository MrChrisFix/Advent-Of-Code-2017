#include "../general.h"
#include <set>

int findAndScore(int cur, set<pair<int, int>> leftoverConnectors)
{
	if (leftoverConnectors.size() == 0)
		return cur;

	int max = 0;
	for (auto& el : leftoverConnectors)
	{
		int score = 0;
		if (el.first == cur)
		{
			set<pair<int, int>> next = leftoverConnectors;
			next.erase(el);
			score += cur + el.second + findAndScore(el.second, next);
		}
		else if (el.second == cur)
		{
			set<pair<int, int>> next = leftoverConnectors;
			next.erase(el);
			score += cur + el.first + findAndScore(el.first, next);
		}

		if (score > max)
			max = score;
	}

	return max;
}

void getPossibleCombinations(int cur, set<pair<int, int>> leftoverConnectors, vector<pair<int, int>>& currentVec, vector<vector<pair<int, int>>>& Combinations)
{
	if (leftoverConnectors.size() == 0)
	{
		Combinations.push_back(currentVec);
		return;
	}

	for (auto& el : leftoverConnectors)
	{
		int score = 0;
		if (el.first == cur)
		{
			set<pair<int, int>> next = leftoverConnectors;
			currentVec.push_back(el);
			next.erase(el);

			getPossibleCombinations(el.second, next, currentVec, Combinations);
			currentVec.pop_back();
		}
		else if (el.second == cur)
		{
			set<pair<int, int>> next = leftoverConnectors;
			currentVec.push_back(el);
			next.erase(el);
			getPossibleCombinations(el.first, next, currentVec, Combinations);
			currentVec.pop_back();
		}
	}

	Combinations.push_back(currentVec);
	return;
}

int calculateScore(vector<pair<int, int>> bridge)
{
	int score = 0;
	for (auto& el : bridge)
	{
		score += el.first + el.second;
	}
	return score;
}


int Day24_Part1(stringstream& input)
{
	set<pair<int, int>> connectors;

	while (!input.eof())
	{
		int num1, num2;
		char slash;
		input >> num1 >> slash >> num2;
		connectors.insert({ num1, num2 });
	}

	int score = findAndScore(0, connectors);

	return score;
}

int Day24_Part2(stringstream& input)
{
	//How to:
	// 1. Create every possible bridge
	// 2. Find the longest
	// 3. Measure it's strength (if multipe then find the strongest)

	set<pair<int, int>> connectors;

	while (!input.eof())
	{
		int num1, num2;
		char slash;
		input >> num1 >> slash >> num2;
		connectors.insert({ num1, num2 });
	}
	vector<pair<int, int>> tmp;
	vector<vector<pair<int, int>>> combinations;

	getPossibleCombinations(0, connectors, tmp, combinations);

	int maxLen = 0, maxScore = 0;
	for (size_t i = 0; i < combinations.size(); i++)
	{
		if (combinations[i].size() > maxLen)
		{
			maxLen = combinations[i].size();
			maxScore = calculateScore(combinations[i]);
		}
		else if (combinations[i].size() == maxLen)
		{
			int points = calculateScore(combinations[i]);
			if (points > maxScore)
				maxScore = points;
		}
	}


	return maxScore;
}


void Day24(stringstream& input)
{
	cout << "Part 1 result is: " << Day24_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day24_Part2(input) << endl << endl;

	return;
}