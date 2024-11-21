#include "../general.h"
#include <map>
#include <thread>
#include <deque>

struct Instruction
{
	string type;
	string X, Y;
};

int Day18_Part1(stringstream& input)
{
	std::map<char, long long> registers;

	vector<Instruction> programm;

	while (!input.eof())
	{
		string instr;
		string X, Y;

		input >> instr >> X;

		Instruction ins;
		ins.type = instr;
		ins.X = X;

		if(!isdigit(X[0]))
			registers[X[0]] = 0;

		if (instr == "set" || instr == "add" || instr == "mod" || instr == "mul" || instr == "jgz")
		{
			input >> Y;
			ins.Y = Y;
		}
		else if (instr == "rcv" || instr == "snd")
		{
			ins.Y = X;
		}

		programm.push_back(ins);
	}

	int cursor = 0;

	vector<int> sounds;

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
			value = registers[newInstr.Y[0]];
		}

		if (type == "jgz")
		{
			if (registers[newInstr.X[0]] > 0)
			{
				cursor += value;
				continue;
			}
		}
		else if (type == "snd")
		{
			sounds.push_back(value);
		}
		else if (type == "set")
		{
			registers[newInstr.X[0]] = value;
		}
		else if (type == "add")
		{
			registers[newInstr.X[0]] += value;
		}
		else if (type == "mul")
		{
			registers[newInstr.X[0]] *= value;
		}
		else if (type == "mod")
		{
			registers[newInstr.X[0]] = registers[newInstr.X[0]] % value;
		}
		else if (type == "rcv")
		{
			if (value != 0)
				return sounds.back();
		}
		else throw;

		cursor++;
	}

	return -1;
}

struct Program
{
	map<char, long long> registers;
	vector<Instruction> programm;

	deque<int>* out;
	deque<int>* in;

	int cursor = 0;
	int sendCounter = 0;

	Program(int num, map<char, long long> regs, const vector<Instruction> programm, deque<int>* out, deque<int>* in)
	{
		registers = regs;
		registers['p'] = num;
		this->programm = programm;
		this->in = in;
		this->out = out;
	}

	void play()
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
				value = registers[newInstr.Y[0]];
			}

			if (type == "jgz")
			{
				if (isdigit(newInstr.X[0]) || newInstr.X[0] == '-')
				{
					if (stoi(newInstr.X) > 0)
					{
						cursor += value;
						continue;
					}
				}
				else if (registers[newInstr.X[0]] > 0)
				{
					cursor += value;
					continue;
				}
			}
			else if (type == "snd")
			{
				out->push_back(value);
				sendCounter++;
			}
			else if (type == "set")
			{
				registers[newInstr.X[0]] = value;
			}
			else if (type == "add")
			{
				registers[newInstr.X[0]] += value;
			}
			else if (type == "mul")
			{
				registers[newInstr.X[0]] *= value;
			}
			else if (type == "mod")
			{
				registers[newInstr.X[0]] = registers[newInstr.X[0]] % value;
			}
			else if (type == "rcv")
			{
				if (in->empty())
					return;

				registers[newInstr.X[0]] = in->front();
				in->pop_front();
			}
			else throw;

			cursor++;
		}
	}
};

int Day18_Part2(stringstream& input)
{
	std::map<char, long long> registers;

	vector<Instruction> programm;

	while (!input.eof())
	{
		string instr;
		string X, Y;

		input >> instr >> X;

		Instruction ins;
		ins.type = instr;
		ins.X = X;

		if (!isdigit(X[0]))
			registers[X[0]] = 0;

		if (instr == "set" || instr == "add" || instr == "mod" || instr == "mul" || instr == "jgz")
		{
			input >> Y;
			ins.Y = Y;
		}
		else if (instr == "rcv" || instr == "snd")
		{
			ins.Y = X;
		}
		programm.push_back(ins);
	}
	deque<int> ZeroToOne, OneToZero;

	Program p0(0, registers, programm, &ZeroToOne, &OneToZero), p1(1, registers, programm, &OneToZero, &ZeroToOne);

	int SentP0 = 0;
	int SentP1 = 0;

	while (true)
	{
		p0.play();
		p1.play();

		if (SentP0 == p0.sendCounter && SentP1 == p1.sendCounter)
			break;

		SentP0 = p0.sendCounter;
		SentP1 = p1.sendCounter;
	}

	return p1.sendCounter;
}


void Day18(stringstream& input)
{
	cout << "Part 1 result is: " << Day18_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day18_Part2(input) << endl << endl;

	return;
}