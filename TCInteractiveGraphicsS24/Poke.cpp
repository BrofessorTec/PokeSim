#include "Poke.h"

Poke::Poke(int id, std::string name, std::string imageurl, int maxHp, int currHp)
{
	this->id = id;
	this->name = name;
	this->imageurl = imageurl;
	this->maxHp = maxHp;
	this->currHp = currHp;
}

int Poke::GetId()
{
	return id;
}

std::string Poke::GetName()
{
	return name;
}

std::string Poke::GetUrl()
{
	return imageurl;
}

int Poke::GetMaxHp()
{
	return maxHp;
}

int Poke::GetCurrHp()
{
	return currHp;
}

void Poke::SetCurrHp(int damage)
{
	currHp -= damage;
	if (currHp < 0)
	{
		currHp = 0;
	}
	else if (currHp > maxHp)
	{
		currHp = maxHp;
	}
}
