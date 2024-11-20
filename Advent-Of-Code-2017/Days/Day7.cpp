#include "../general.h"
#include <map>
#include <set>


string Day7_Part1(stringstream& input)
{
	std::map<std::string, std::vector<std::string>> connections;
	std::set<std::string> names;

	while (!input.eof())
	{
		std::string sline;
		getline(input, sline);
		std::stringstream line(sline);

		std::string name, stuff;

		line >> name >> stuff;

		if (!line.eof())
			line >> stuff; //arrow

		while (!line.eof())
		{
			line >> stuff;
			if (stuff.ends_with(','))
				stuff.pop_back();

			names.insert(stuff);
			connections[name].push_back(stuff);
		}
	}

	for (auto& el : connections)
	{
		if (!names.contains(el.first))
			return el.first;
	}

	return "Something went wrong";
}

struct Node //The methods are quite a mess, but it works
{
	std::string name;
	std::vector<Node*> children;
	int weight;

	Node(std::string Name, int Weight) : name(Name), weight(Weight) {}

	int getTotalWieight()
	{
		int sum = weight;

		for (auto& ch : children)
			sum += ch->getTotalWieight();

		return sum;
	}

	std::string findProgram()
	{
		if (children.size() == 0)
			return "-1";


		std::vector<int> weights(children.size());
		for (int i = 0; i < weights.size(); i++)
		{
			weights[i] = children[i]->getTotalWieight();
		}
		auto temp = weights;
		int val;
		std::sort(temp.begin(), temp.end());
		if (temp[0] == temp[1] && temp[temp.size() - 1] != temp[temp.size() - 2])
		{
			val = temp[temp.size() - 1];
		}
		else if (temp[temp.size() - 1] == temp[temp.size() - 2] && temp[0] != temp[1])
		{
			val = temp[0];
		}
		else
			return name;

		for (int i = 0; i < weights.size(); i++)
		{
			if (weights[i] == val)
			{
				return children[i]->findProgram();
			}
		}
	}

	int findRightWeight(std::string &programName)
	{
		for (int i = 0; i < children.size(); i++)
		{
			if (children[i]->name == programName)
			{
				std::vector<int> weights(children.size());
				for (int i = 0; i < weights.size(); i++)
				{
					weights[i] = children[i]->getTotalWieight();
				}

				std::sort(weights.begin(), weights.end());

				if (weights[0] == weights[1] && weights[weights.size() - 1] != weights[weights.size() - 2])
				{
					return children[i]->weight - (weights[weights.size() - 1] - weights[weights.size() - 2]);
				}
				else
				{
					return children[i]->weight + (weights[1] - weights[0]);
				}

				return 0;
			}
			else
			{
				int val = children[i]->findRightWeight(programName);
				if (val != -1)
					return val;
			}
		}
		return -1;
	}

	void addChildren(
		std::map<std::string, std::vector<std::string>>& connections,
		std::set<std::string>& names,
		std::map<std::string, int>& values
	)
	{
		for (auto& ch : connections[name])
		{
			Node* child = new Node(ch, values[ch]);
			children.push_back(child);
			child->addChildren(connections, names, values);
		}
	}

	~Node()
	{
		for (auto ch : children)
		{
			delete ch;
			ch = nullptr;
		}
	}

};


int Day7_Part2(stringstream& input)
{
	std::map<std::string, std::vector<std::string>> connections;
	std::set<std::string> names;
	std::map<std::string, int> values;

	while (!input.eof())
	{
		std::string sline;
		getline(input, sline);
		std::stringstream line(sline);

		std::string name, stuff;
		int value;
		char trash;

		line >> name >> trash >> value >> trash;

		values[name] = value;

		if (!line.eof())
			line >> stuff; //arrow

		while (!line.eof())
		{
			line >> stuff;
			if (stuff.ends_with(','))
				stuff.pop_back();

			names.insert(stuff);
			connections[name].push_back(stuff);
		}
	}

	Node* start = nullptr;

	for (auto& el : connections)
	{
		if (!names.contains(el.first))
		{
			start = new Node(el.first, values[el.first]);
			break;
		}
	}

	start->addChildren(connections, names, values);

	std::string wrongProgram = start->findProgram();
	int result = start->findRightWeight(wrongProgram);

	delete start;
	start = nullptr;

	return result;
}


void Day7(stringstream& input)
{
	cout << "Part 1 result is: " << Day7_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day7_Part2(input) << endl << endl;

	return;
}