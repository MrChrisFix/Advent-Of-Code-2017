#include "../general.h"
#include <algorithm>
#include <set>

struct V3
{
	long long x, y, z;

	V3 operator+(const V3& rhs)
	{
		V3 v3{ x,y,z };
		v3.x += rhs.x;
		v3.y += rhs.y;
		v3.z += rhs.z;
		return v3;
	}

	V3& operator=(const V3& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *this;
	}

	V3& operator+=(const V3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	int getDistance() const
	{
		return abs(x) + abs(y) + abs(z);
	}

	bool operator==(const V3& rhs) const
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z);
	}

	bool operator<(const V3& rhs) const
	{
		return getDistance() < rhs.getDistance();
	}

};

int Day20_Part1(stringstream& input)
{
	vector<V3> particles;
	vector<V3> velocities;
	vector<V3> accelerations;

	while (!input.eof())
	{
		string sline;
		getline(input, sline);
		if (sline.empty())
			break;
		stringstream line(sline);
		char t;
		long long x, y, z;

		line >> t >> t >> t >> x >> t >> y >> t >> z >> t >> t;
		V3 part{ x,y,z };
		particles.push_back(part);

		line >> t >> t >> t >> x >> t >> y >> t >> z >> t >> t;
		V3 vel{ x,y,z };
		velocities.push_back(vel);

		line >> t >> t >> t >> x >> t >> y >> t >> z >> t >> t;
		V3 acc{ x,y,z };
		accelerations.push_back(acc);
	}

	vector<long long> distances(particles.size());

	int nearestIdx = 0;
	int record = 0;

	while (record < 1000)
	{
		for (int i = 0; i < velocities.size(); i++)
		{
			velocities[i] += accelerations[i];
			particles[i] += velocities[i];
			distances[i] = particles[i].getDistance();
		}

		auto minIt = min_element(distances.begin(), distances.end());
		int minIdx = distance(distances.begin(), minIt);

		if (minIdx == nearestIdx)
		{
			record++;
		}
		else
		{
			nearestIdx = minIdx;
			record = 1;
		}
	}

	return nearestIdx;
}

struct Particle
{
	V3 position;
	V3 velocity;
	V3 acceleretion;

	bool dead = false;

	void update()
	{
		velocity += acceleretion;
		position += velocity;
	}
};


int Day20_Part2(stringstream& input)
{
	vector<Particle> particles;

	while (!input.eof())
	{
		string sline;
		getline(input, sline);
		if (sline.empty())
			break;
		stringstream line(sline);
		char t;
		long long x, y, z;
		Particle particle;

		line >> t >> t >> t >> x >> t >> y >> t >> z >> t >> t;
		particle.position = { x,y,z };
		
		line >> t >> t >> t >> x >> t >> y >> t >> z >> t >> t;
		particle.velocity = { x,y,z };
		
		line >> t >> t >> t >> x >> t >> y >> t >> z >> t >> t;
		particle.acceleretion = { x,y,z };

		particles.push_back(particle);
	}
	int cnt = 0;
	while (cnt++ < 1000)
	{
		for (int i = 0; i < particles.size(); i++)
		{
			if (particles[i].dead)
				continue;
			particles[i].update();
		}

		// a bit slow, could use maps/sets for counting positions, but it works now
		for (int i = 0; i < particles.size(); i++)
		{
			if (particles[i].dead)
				continue;
			for (int j = i + 1; j < particles.size(); j++)
			{
				if (particles[i].position == particles[j].position)
				{
					particles[i].dead = true;
					particles[j].dead = true;
				}
			}
		}
	}

	int val = count_if(particles.begin(), particles.end(), [](Particle& part) { return !part.dead; });

	return val;
}

void Day20(stringstream& input)
{
	cout << "Part 1 result is: " << Day20_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day20_Part2(input) << endl << endl;

	return;
}