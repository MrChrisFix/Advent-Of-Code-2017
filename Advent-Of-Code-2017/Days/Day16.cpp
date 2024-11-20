#include "../general.h"
#include <numeric>

string Day16_Part1(stringstream& input)
{
	std::string programs;
	programs.resize(16);
	std::iota(programs.begin(), programs.end(), 'a');

	while (!input.eof())
	{
		char c = input.get();

		if (c == 's') //spin
		{
			int X;
			input >> X;

			std::rotate(programs.rbegin(), programs.rbegin() + X, programs.rend());

		}
		else if (c == 'x') //exchange
		{
			int A, B;
			input >> A >> c >> B;

			char tmp = programs[A];
			programs[A] = programs[B];
			programs[B] = tmp;

		}
		else //partner
		{
			char A, B;
			input >> A >> c >> B;

			auto Apos = programs.find(A);
			auto Bpos = programs.find(B);

			char tmp = programs[Apos];
			programs[Apos] = programs[Bpos];
			programs[Bpos] = tmp;
		}

		input >> c; //comma
	}
	return programs;
}

string Day16_Part2(stringstream& input)
{
	std::string programs;
	programs.resize(16);
	std::iota(programs.begin(), programs.end(), 'a');

	for (size_t i = 0; i < 1000000000 % 30; i++)
	{
		std::string sline = input.str();
		input.seekg(0);
		stringstream once(sline);

		while (!once.eof())
		{
			char c = once.get();

			if (c == 's') //spin
			{
				int X;
				once >> X;

				std::rotate(programs.rbegin(), programs.rbegin() + X, programs.rend());

			}
			else if (c == 'x') //exchange
			{
				int A, B;
				once >> A >> c >> B;

				char tmp = programs[A];
				programs[A] = programs[B];
				programs[B] = tmp;

			}
			else //partner
			{
				char A, B;
				once >> A >> c >> B;

				auto Apos = programs.find(A);
				auto Bpos = programs.find(B);

				char tmp = programs[Apos];
				programs[Apos] = programs[Bpos];
				programs[Bpos] = tmp;
			}

			once >> c; //comma
		}
	}

	return programs;
}


void Day16(stringstream& input)
{
	cout << "Part 1 result is: " << Day16_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day16_Part2(input) << endl << endl;

	return;
}