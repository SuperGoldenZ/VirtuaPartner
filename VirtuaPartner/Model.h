#pragma once

#ifndef MODEL
#define MODEL

#include <string>
#include <vector>
#include <map>

#include "PunishStats.h"
#include "CharacterCommands.h"

class Model
{
private:
	void readConfigYamlFile(std::string filename);

public:
	std::string player1Character;
	std::string player2Character;
	std::string selectedCategory = "";

	int playerToSelect = -1;
	
	//If CPU is on the left side or not
	bool leftSide = false;

	//Whether to give feedback on guaranteed punish damage or not
	bool punishCheck = true;

	unsigned int stringIndex = 1;
	CharacterCommands characterCommands;

	Model();

	std::map<std::string, PunishStats> punishStats;
	std::map<std::string, bool> selectedStrings;	
	std::string currentCpuCharacter = "";
	std::vector<std::string> stringArray;
	std::vector<std::string> getStrings(std::string category);
	bool updateSelectedPlayers(std::string newPlayer1Character, std::string newPlayer2Character);
	//int getCurrentCategoryIndex();
	void loadConfigFiles();
	std::string categoryToString(std::string category);

	void selectNextCategory();
};

#endif