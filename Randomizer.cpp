#include "Randomizer.h"


int Randomizer::last = 0;
Randomizer::Randomizer()
{
}
int Randomizer::next()
{
	srand(std::time(0));
	int r = rand() % 7;
	if (last == r) r = rand() % 7;
	while (r == 7) {
		r = rand() % 7;
	}
	last = r;
	return r;
}

Randomizer::~Randomizer()
{
}
