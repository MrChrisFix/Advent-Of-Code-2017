#include "../general.h"
#include <map>
#include <set>

void visit(int current, std::map<int, std::vector<int>>& connections, std::set<int>& visited)
{
	if (visited.contains(current))
		return;

	visited.insert(current);
	for (auto& el : connections[current])
	{
		visit(el, connections, visited);
	}
}

int Day12_Part1(stringstream& input)
{
	std::map<int, std::vector<int>> connections;
	std::set<int> visited;

	while (!input.eof())
	{
		std::string sline;
		getline(input, sline);
		std::stringstream line(sline);

		int num1, numElse;
		std::string trash;

		line >> num1 >> trash >> numElse >> trash;

		connections[num1].push_back(numElse);

		while (!line.eof())
		{
			line >> numElse >> trash;
			connections[num1].push_back(numElse);
		}
	}

	visit(0, connections, visited);


	return visited.size();
}

int Day12_Part2(stringstream& input)
{
	std::map<int, std::vector<int>> connections;
	std::set<int> visited;

	while (!input.eof())
	{
		std::string sline;
		getline(input, sline);
		std::stringstream line(sline);

		int num1, numElse;
		std::string trash;

		line >> num1 >> trash >> numElse >> trash;

		connections[num1].push_back(numElse);

		while (!line.eof())
		{
			line >> numElse >> trash;
			connections[num1].push_back(numElse);
		}
	}

	int groups = 0;

	for (auto& el : connections)
	{
		if (visited.contains(el.first))
			continue;

		visit(el.first, connections, visited);
		groups++;
	}

	return groups;
}


void Day12(stringstream& input)
{
	cout<<"Part 1 result is: " << Day12_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day12_Part2(input)<<endl<<endl;

	return;
}