#include "../general.h"
#include <map>


int Day8_Part1(stringstream& input)
{
	std::map<std::string, int> registers;

	while (!input.eof())
	{
		std:string sline;
		getline(input, sline);
		std::stringstream line(sline);
		
		std::string reg, if_reg, instr, cond;
		int val, if_val;

		line >> reg >> instr >> val >> cond >> if_reg >> cond >> if_val;



		if (cond == "<" && registers[if_reg] < if_val ||
			cond == "<=" && registers[if_reg] <= if_val ||
			cond == ">" && registers[if_reg] > if_val ||
			cond == ">=" && registers[if_reg] >= if_val ||
			cond == "==" && registers[if_reg] == if_val ||
			cond == "!=" && registers[if_reg] != if_val
			)
		{
			registers[reg] += (instr == "inc" ? val : -val);
		}

	}

	int max = (*registers.begin()).second;

	for (auto& reg : registers)
	{
		if (reg.second > max)
			max = reg.second;
	}

	return max;
}

int Day8_Part2(stringstream& input)
{
	std::map<std::string, int> registers;

	int highest = 0;

	while (!input.eof())
	{
	std:string sline;
		getline(input, sline);
		std::stringstream line(sline);

		std::string reg, if_reg, instr, cond;
		int val, if_val;

		line >> reg >> instr >> val >> cond >> if_reg >> cond >> if_val;

		if (cond == "<" && registers[if_reg] < if_val ||
			cond == "<=" && registers[if_reg] <= if_val ||
			cond == ">" && registers[if_reg] > if_val ||
			cond == ">=" && registers[if_reg] >= if_val ||
			cond == "==" && registers[if_reg] == if_val ||
			cond == "!=" && registers[if_reg] != if_val
			)
		{
			registers[reg] += (instr == "inc" ? val : -val);

			if (registers[reg] > highest)
				highest = registers[reg];
		}

	}

	return highest;
}


void Day8(stringstream& input)
{
	cout<<"Part 1 result is: " << Day8_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day8_Part2(input)<<endl<<endl;

	return;
}