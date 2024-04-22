#pragma once
#include "GraphicsObject.h"

class ObjectManager
{
private:
	std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> objectsMap;
	std::string currPokeSel = "Venusaurplayer";
	std::string currEnemy = "poke2";
	std::string sel1 = "Dragoniteplayer";
	std::string sel2 = "Mewtwoplayer";


public:
	void SetObject(std::string key, std::shared_ptr<GraphicsObject> graphObj);
	std::shared_ptr<GraphicsObject> GetObject(std::string key);
	std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> GetObjectMap();
	void Update(double elapsedSeconds);
	void SetBehaviorDefaults();
	std::string GetCurrPokeSel();
	void SetCurrPokeSel(std::string newSel);
	std::string GetPoke1Sel();
	void SetPoke1Sel(std::string newSel);
	std::string GetPoke2Sel();
	void SetPoke2Sel(std::string newSel);
	std::string GetCurrEnemy();
	void SetCurrEnemy(std::string newSel);
};

