#pragma once

#include <string>
#include <map>
#include <vector>

class CharacterCommands
{
private:	
	std::map < std::string, std::vector<std::string>> categories;
	std::map < std::string, std::vector<std::string>> commands;

public:
	int numCharactersLoaded = 0;
	std::string characterNames[19];
	void addCharacterName(const std::string);	
	void addCategoryName(const std::string characterName, const std::string categoryName);
	void addCommand(const std::string characterName, const std::string categoryName, const std::string command);
	std::vector<std::string> getCommands(const std::string characterName, const std::string categoryName);
	void clear();
	std::vector<std::string> getCategories(const std::string characterName);
	std::string getNextCategory(const std::string characterName, const std::string categoryName);
	std::string getPreviousCategory(const std::string characterName, const std::string categoryName);
	std::string getNextCommand(const std::string characterName, const std::string categoryName, const std::string command);
	std::string getPreviousCommand(const std::string characterName, const std::string categoryName, const std::string command);
	std::string getRandomCommand(const std::string characterName, const std::string categoryName);
};

