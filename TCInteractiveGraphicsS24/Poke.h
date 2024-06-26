#pragma once
#include <string>

class Poke
{
private:
	int id;
	std::string name;
	std::string imageurl;
	int maxHp;
	int currHp;
public:
	Poke(int id, std::string name, std::string imageurl, int maxHp = 10, int currHp = 10);
	int GetId();
	std::string GetName();
	std::string GetUrl();
	int GetMaxHp();
	int GetCurrHp();
	void SetCurrHp(int damage);
};

