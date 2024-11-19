#include "../general.h"
#include <set>

int Day4_Part1(stringstream& input)
{
	int sum = 0;

	while (!input.eof())
	{
		std::string sline;
		getline(input, sline);
		std::stringstream line(sline);

		int count = 0;
		std::set<std::string> words;
		while (!line.eof())
		{
			std::string passphrase;
			line >> passphrase;
			count++;
			words.insert(passphrase);
		}

		if (words.size() == count)
			sum++;
	}
	return sum;
}

int Day4_Part2(stringstream& input)
{
	int sum = 0;

	while (!input.eof())
	{
		std::string sline;
		getline(input, sline);
		std::stringstream line(sline);

		int count = 0;
		std::set<std::string> words;
		while (!line.eof())
		{
			std::string passphrase;
			line >> passphrase;
			count++;

			sort(passphrase.begin(), passphrase.end());

			words.insert(passphrase);
		}

		if (words.size() == count)
			sum++;
	}
	return sum;
}


void Day4(stringstream& input)
{
	cout<<"Part 1 result is: " << Day4_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day4_Part2(input)<<endl<<endl;

	return;
}