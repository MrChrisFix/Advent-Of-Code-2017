#include "../general.h"
#include <map>

struct State
{
	char name;
	int writeVal[2];
	char nextState[2];
	int direction[2];

	State() {}

	State(char stateName)
	{
		name = stateName;
	};

	void setAtVal(int value, int write, char next, int dir)
	{
		if (value != 1 && value != 0)
			throw;

		writeVal[value] = write;
		nextState[value] = next;
		direction[value] = dir;
	}

	void execute(int readValue, int& writeValue, char& nextstate, int& dir) const
	{
		if (readValue != 1 && readValue != 0)
			throw;

		writeValue = writeVal[readValue];
		nextstate = nextState[readValue];
		dir = direction[readValue];
	}

};


int Day25_Part1(stringstream& input)
{
	map<char, State> States;

	string slines;
	getline(input, slines);
	char nextState = slines[slines.size() - 2];
	size_t steps;
	input >> slines >> slines >> slines >> slines >> slines >> steps >> slines;

	while (!input.eof())
	{
		getline(input, slines);
		if (slines.empty())
			continue;
		char stateName = slines[slines.size() - 2];

		State newState(stateName);

		int writeVal;
		string direction;

		getline(input, slines); //if 0
		getline(input, slines); //write
		writeVal = slines[slines.size() - 2] - '0';
		input >> slines >> slines >> slines >> slines >> slines >> slines >> direction;
		direction.pop_back(); //dot
		getline(input, slines); //next line
		getline(input, slines); //Continue with...
		char stateAfter = slines[slines.size() - 2];

		newState.setAtVal(0, writeVal, stateAfter, (direction == "right" ? 1 : -1));

		getline(input, slines); //if 1
		getline(input, slines); //write
		writeVal = slines[slines.size() - 2] - '0';
		input >> slines >> slines >> slines >> slines >> slines >> slines >> direction;
		direction.pop_back(); //dot
		getline(input, slines); //next line
		getline(input, slines); //Continue with...
		stateAfter = slines[slines.size() - 2];

		newState.setAtVal(1, writeVal, stateAfter, (direction == "right" ? 1 : -1));

		States[stateName] = newState;
	}

	long long curPos = 0;

	map<int, bool> tape;

	int write, direction;
	char next;

	for (size_t i = 0; i < steps; i++)
	{
		int value = tape[curPos];

		States[nextState].execute(value, write, nextState, direction);

		tape[curPos] = write;
		curPos += direction;
	}


	int result = 0;
	for (auto& el : tape)
	{
		if (el.second)
			result++;
	}

	return result;
}

string Day25_Part2(stringstream& input)
{
	return "The End :)";
}


void Day25(stringstream& input)
{
	cout << "Part 1 result is: " << Day25_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day25_Part2(input) << endl << endl;

	return;
}