#include "player.h"

player::player(int scoreinput, std::string nameinput)
{

	score = scoreinput;
	name = nameinput;

}

bool player::operator<(const player& player)const
{
	return score< player.score ;
}
