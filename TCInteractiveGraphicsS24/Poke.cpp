#include "Poke.h"

Poke::Poke(int id, std::string name, std::string imageurl, int maxHp, int currHp)
{
	this->id = id;
	this->name = name;
	this->imageurl = imageurl;
	this->maxHp = maxHp;
	this->currHp = currHp;
}
