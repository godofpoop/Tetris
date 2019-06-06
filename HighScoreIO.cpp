#include "HighScoreIO.h"



HighScoreIO::HighScoreIO()
{
}
bool HighScoreIO::write(int score,std::vector<int> &t)
{
	bool res = false;
	std::ifstream file("highscores.txt");
	t.clear();
	std::string line;

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		int temp;
		ss >> temp;
		t.push_back(temp);
	}
	for (int i = 0; i < t.size(); i++) {
		if (score > t[i]) {
			res = true;
			for (int j = t.size()-1; j > i; j--) {
				t[j] = t[j-1];
			}
			t[i] = score;
			break;
		}
	}
	file.close();

	std::ofstream out("highscores.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < t.size(); i++) {
		out << t[i] << "\n";
	}
	out.close();

	return res;
}

HighScoreIO::~HighScoreIO()
{
}
