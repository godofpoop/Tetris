#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class HighScoreIO
{
public:
	HighScoreIO();
	static bool write(int score,std::vector<int> &t);
	~HighScoreIO();
};

