#include "../general.h"
#include <set>
#include <map>

set<string> permutate(string input)
{
	set<string> res;

	if (input.size() == 5) //2x2
	{
		string seg1 = input.substr(0, 2), seg2 = input.substr(3, 2);

		res.insert(seg1 + seg2);
		res.insert(seg2 + seg1);

		swap(seg1[0], seg2[1]);
		res.insert(seg1 + seg2);
		res.insert(seg2 + seg1);

		swap(seg1[0], seg1[1]);
		swap(seg2[0], seg2[1]);
		res.insert(seg1 + seg2);
		res.insert(seg2 + seg1);

	}
	else //3x3
	{
		string seg1 = input.substr(0, 3), seg2 = input.substr(4, 3), seg3 = input.substr(8, 3);

		res.insert(seg1 + seg2 + seg3);
		res.insert(seg3 + seg2 + seg1);

		//vertical flip:
		swap(seg1[0], seg1[2]);
		swap(seg2[0], seg2[2]);
		swap(seg3[0], seg3[2]);
		res.insert(seg1 + seg2 + seg3);
		res.insert(seg3 + seg2 + seg1);
		//Undo
		swap(seg1[0], seg1[2]);
		swap(seg2[0], seg2[2]);
		swap(seg3[0], seg3[2]);

		//rotate right once:
		char r[4] = { seg1[0], seg1[2], seg3[2], seg3[0] };
		char c[4] = { seg1[1], seg2[2], seg3[1], seg2[0] };

		seg1[0] = r[3];
		seg1[2] = r[0];
		seg3[2] = r[1];
		seg3[0] = r[2];

		seg1[1] = c[3];
		seg2[2] = c[0];
		seg3[1] = c[1];
		seg2[0] = c[2];

		res.insert(seg1 + seg2 + seg3);
		res.insert(seg3 + seg2 + seg1);

		swap(seg1[0], seg1[2]);
		swap(seg2[0], seg2[2]);
		swap(seg3[0], seg3[2]);
		res.insert(seg1 + seg2 + seg3);
		res.insert(seg3 + seg2 + seg1);
		//Undo
		swap(seg1[0], seg1[2]);
		swap(seg2[0], seg2[2]);
		swap(seg3[0], seg3[2]);

	}

	return res;
}

std::string EnchancePainting(int iterations, string painting, map<std::string, std::string>& enhancement)
{
	for (int i = 0; i < iterations; i++)
	{
		int side = sqrt(painting.size());

		string nextPainting;

		if (side % 2 == 0)
		{
			int grids = painting.size() / 4;

			int nextSideSize = (side / 2) * 3;
			nextPainting.resize(nextSideSize * nextSideSize);

			for (int grid = 0; grid < grids; grid++)
			{
				int x = (grid * 2) % side;  //0,2,0,2... lub 0,2,4,6, 0,2,4,6...
				int y = 2 * ((2 * grid) / side);  //0,0,2,2 lub 0,0,0,0, 2,2,2,2

				int corner = x + y * side;

				string subgrid = { painting[corner], painting[corner + 1], painting[corner + side], painting[corner + side + 1] };

				string enhanced = enhancement[subgrid];

				int xx = (3 * grid) % nextSideSize; //0, 3, 0 ,3 or 0,3,6, 0,3,6...
				int yy = 3 * ((3 * grid) / nextSideSize); //0,0,3,3 or 0,0,0, 3,3,3, 6,6,6

				int cc = xx + yy * nextSideSize; // 0, 3, 18, 21
				int skip = nextSideSize;

				nextPainting[cc] = enhanced[0];
				nextPainting[cc + 1] = enhanced[1];
				nextPainting[cc + 2] = enhanced[2];

				nextPainting[cc + skip] = enhanced[3];
				nextPainting[cc + 1 + skip] = enhanced[4];
				nextPainting[cc + 2 + skip] = enhanced[5];

				nextPainting[cc + 2 * skip] = enhanced[6];
				nextPainting[cc + 1 + 2 * skip] = enhanced[7];
				nextPainting[cc + 2 + 2 * skip] = enhanced[8];
			}
		}
		else
		{
			int grids = painting.size() / 9;
			int nextSideSize = (side / 3) * 4;
			nextPainting.resize(nextSideSize * nextSideSize);

			for (int grid = 0; grid < grids; grid++)
			{
				int x = (3 * grid) % side;
				int y = 3 * ((3 * grid) / side);

				int corner = x + y * side;

				string subgrid = {
					painting[x], painting[corner + 1], painting[corner + 2],
					painting[corner + side], painting[corner + side + 1], painting[corner + side + 2],
					painting[corner + 2 * side], painting[corner + 2 * side + 1], painting[corner + 2 * side + 2]
				};

				string enhanced = enhancement[subgrid];

				int xx = (4 * grid) % nextSideSize; //0, 4, 0, 4
				int yy = 4 * ((4 * grid) / nextSideSize); //0,0,4,4

				int cc = xx + yy * nextSideSize; // 0, 3, 18, 21

				int skip = nextSideSize;

				nextPainting[cc] = enhanced[0];
				nextPainting[cc + 1] = enhanced[1];
				nextPainting[cc + 2] = enhanced[2];
				nextPainting[cc + 3] = enhanced[3];

				nextPainting[cc + skip] = enhanced[4];
				nextPainting[cc + 1 + skip] = enhanced[5];
				nextPainting[cc + 2 + skip] = enhanced[6];
				nextPainting[cc + 3 + skip] = enhanced[7];

				nextPainting[cc + 2 * skip] = enhanced[8];
				nextPainting[cc + 1 + 2 * skip] = enhanced[9];
				nextPainting[cc + 2 + 2 * skip] = enhanced[10];
				nextPainting[cc + 3 + 2 * skip] = enhanced[11];

				nextPainting[cc + 3 * skip] = enhanced[12];
				nextPainting[cc + 1 + 3 * skip] = enhanced[13];
				nextPainting[cc + 2 + 3 * skip] = enhanced[14];
				nextPainting[cc + 3 + 3 * skip] = enhanced[15];
			}
		}

		painting = nextPainting;
	}

	return painting;
}


int Day21_Part1(stringstream& input)
{
	string painting = ".#...####";

	map<std::string, std::string> enhancement;

	while (!input.eof())
	{
		string sline;
		getline(input, sline);
		stringstream line(sline);
		string from, to;
		line >> from >> to >> to;

		auto permutations = permutate(from);

		to.erase(std::remove(to.begin(), to.end(), '/'), to.end());

		for (auto& el : permutations)
		{
			enhancement[el] = to;
		}
	}

	painting = EnchancePainting(5, painting, enhancement);

	int res = count(painting.begin(), painting.end(), '#');

	return res;
}

int Day21_Part2(stringstream& input)
{
	string painting = ".#...####";

	map<std::string, std::string> enhancement;

	while (!input.eof())
	{
		string sline;
		getline(input, sline);
		stringstream line(sline);
		string from, to;
		line >> from >> to >> to;

		auto permutations = permutate(from);

		to.erase(std::remove(to.begin(), to.end(), '/'), to.end());

		for (auto& el : permutations)
		{
			enhancement[el] = to;
		}
	}

	painting = EnchancePainting(18, painting, enhancement);

	int res = count(painting.begin(), painting.end(), '#');

	return res;
}


void Day21(stringstream& input)
{
	cout << "Part 1 result is: " << Day21_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day21_Part2(input) << endl << endl;

	return;
}