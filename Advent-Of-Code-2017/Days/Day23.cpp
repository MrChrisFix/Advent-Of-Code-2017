#include "../general.h"
#include <map>

struct Instruction
{
	string type;
	string X, Y;
};

struct ProgramV2
{
	map<char, long long>* registers;
	vector<Instruction> programm;

	int cursor = 0;
	int mulCounter = 0;

	ProgramV2(map<char, long long>* regs, const vector<Instruction> programm)
	{
		registers = regs;
		this->programm = programm;
	}

	void run()
	{
		while (cursor < programm.size())
		{
			Instruction newInstr = programm[cursor];

			string type = newInstr.type;

			int value;

			if (isdigit(newInstr.Y[0]) || newInstr.Y[0] == '-')
			{
				value = stoi(newInstr.Y);
			}
			else
			{
				value = (*registers)[newInstr.Y[0]];
			}

			if (type == "jnz")
			{
				if (isdigit(newInstr.X[0]) || newInstr.X[0] == '-')
				{
					if (stoi(newInstr.X) != 0)
					{
						cursor += value;
						continue;
					}
				}
				else if ((*registers)[newInstr.X[0]] != 0)
				{
					cursor += value;
					continue;
				}
			}
			else if (type == "set")
			{
				(*registers)[newInstr.X[0]] = value;
			}
			else if (type == "sub")
			{
				(*registers)[newInstr.X[0]] -= value;
			}
			else if (type == "mul")
			{
				(*registers)[newInstr.X[0]] *= value;
				mulCounter++;
			}
			else throw;

			cursor++;
		}
	}
};


int Day23_Part1(stringstream& input)
{
	if (input.str().empty())
		return -1;

	std::map<char, long long> registers;
	registers['a'] = 0;
	registers['b'] = 0;
	registers['c'] = 0;
	registers['d'] = 0;
	registers['e'] = 0;
	registers['f'] = 0;
	registers['g'] = 0;
	registers['h'] = 0;

	vector<Instruction> programm;

	while (!input.eof())
	{
		string instr;
		string X, Y;

		input >> instr >> X >> Y;

		Instruction ins;
		ins.type = instr;
		ins.X = X;
		ins.Y = Y;

		programm.push_back(ins);
	}
	ProgramV2 prog(&registers, programm);

	prog.run();

	return prog.mulCounter;
}

int Day23_Part2(stringstream& input)
{
	//puzzle input assembly code optimized and rewritten in C++

	const int  c = 122700;
	int b = 105700, h = 0;

	while (true)
	{
		int i = 2;
		for (i = 2; i < b; i++)
		{
			if (b % i == 0)
			{
				h++;
				break;
			}
		}

		if (b == c)
			break;

		b += 17;
	}

	return h;
}


void Day23(stringstream& input)
{
	cout << "Part 1 result is: " << Day23_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day23_Part2(input) << endl << endl;

	return;
}