#pragma once

#include <string>
class player
{

public:
	std::string name;
	int score;


	player(int scoreinput, std::string nameinput);

	bool operator<(const player &player) const;

};

