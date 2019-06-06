#pragma once
#include <random>
#include <ctime>
class Randomizer
{
public:
	Randomizer();
	static int next();
	~Randomizer();
private:
	static int last;
};

