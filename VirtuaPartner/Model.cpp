#include "Model.h"

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <cstring>
#include <iostream>
#include "CharacterCommands.h"

Model::Model()
{

}

bool hasEnding(std::string const& fullString, std::string const& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

void Model::loadConfigFiles()
{
	characterCommands.clear();
	//currentCpuCharacter = "";
	//selectedCategory = "";

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;

	hFind = FindFirstFile(_T("configs\\*"), &ffd);
	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			std::string configFile;
			configFile += "configs\\";
			std::wstring wFileName(ffd.cFileName);
			std::string filename(wFileName.begin(), wFileName.end());
			if (hasEnding(filename, ".yml")) {
				configFile += filename;
				readConfigYamlFile(configFile);
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);
}

/*
int Model::getCurrentCategoryIndex()
{
int currentCategoryIndex = -1;
for (int i = 0; i < 19; i++) {
if (allCharacterCpuCommandStrings[i][0] == currentCpuCharacter) {
currentCategoryIndex = i;
break;
}
}

return currentCategoryIndex;
}*/

void Model::readConfigYamlFile(std::string filename)
{
	std::vector<std::string> strings;

	std::ifstream file(filename);
	std::string characterName;
	std::string categoryName;
	std::string commandString;

	bool processingCategories = false;
	if (file.is_open()) {
		for (std::string line; getline(file, line);) {
			if (line[0] != '#' && !line.empty()) {
				if (line.rfind("CharacterName: ", 0) == 0) {
					line.erase(std::remove(line.begin(), line.end(), '"'), line.end());

					characterName = line.substr(15);

					if (currentCpuCharacter == "") {
						currentCpuCharacter = characterName;
					}

					characterCommands.addCharacterName(characterName);
				}
				else if (line.rfind("Categories:", 0) == 0) {
					processingCategories = true;
				}
				else if (processingCategories) {
					if (line.find("-") == 2) {
						categoryName = line.substr(4);
						characterCommands.addCategoryName(characterName, categoryName);

						if (selectedCategory == "") {
							selectedCategory = categoryName;
						}
					}
					else {
						if (line.find("-") == 4) {
							commandString = line.substr(6);
							characterCommands.addCommand(characterName, categoryName, commandString);

							if (selectedCommand == "") {
								selectedCommand = commandString;
							}
						}
					}
				}
				strings.push_back(line);
			}

			if (characterName.empty()) {
				characterName = line;
			}
		}
	}
}

std::vector<std::string> Model::getStrings(std::string category) {
	return characterCommands.getCommands(player2Character, category);
}

bool Model::updateSelectedPlayers(std::string newPlayer1Character, std::string newPlayer2Character)
{
	bool updated = false;

	if (player1Character != newPlayer1Character && newPlayer1Character != "Unknown") {
		player1Character = newPlayer1Character;
		updated = true;
	}

	if (player2Character != newPlayer2Character && newPlayer2Character != "Unknown") {
		player2Character = newPlayer2Character;
		if (player2Character == "Akira") {
			currentCpuCharacter = "[A]kira";
		}
		else if (player2Character == "Aoi") {
			currentCpuCharacter = "A[o]i";
		}
		else if (player2Character == "Blaze") {
			currentCpuCharacter = "Bla[z]e";
		}
		else if (player2Character == "Brad") {
			currentCpuCharacter = "[B]rad";
		}
		else if (player2Character == "Eileen") {
			currentCpuCharacter = "[E]ileen";
		}
		else if (player2Character == "Goh") {
			currentCpuCharacter = "[G]oh";
		}
		else if (player2Character == "Jacky") {
			currentCpuCharacter = "Ja[c]ky";
		}
		else if (player2Character == "Jean") {
			currentCpuCharacter = "[J]ean";
		}
		else if (player2Character == "Jeffry") {
			currentCpuCharacter = "Jeff[r]y";
		}
		else if (player2Character == "Lion") {
			currentCpuCharacter = "L[i]on";
		}
		else if (player2Character == "Sarah") {
			currentCpuCharacter = "[S]arah";
		}
		else if (player2Character == "Lau") {
			currentCpuCharacter = "[L]au";
		}
		else if (player2Character == "Kage") {
			currentCpuCharacter = "[K]age";
		}
		else if (player2Character == "Lau") {
			currentCpuCharacter = "[L]au";
		}
		else if (player2Character == "Pai") {
			currentCpuCharacter = "[P]ai";
		}
		else if (player2Character == "Shun") {
			currentCpuCharacter = "S[h]un";
		}
		else if (player2Character == "Taka") {
			currentCpuCharacter = "[T]aka";
		}
		else if (player2Character == "Vanessa") {
			currentCpuCharacter = "[V]anessa";
		}
		else if (player2Character == "Wolf") {
			currentCpuCharacter = "[W]olf";
		}
		else if (player2Character == "Lei-Fei") {
			currentCpuCharacter = "Lei-[F]ei";
		}

		updated = true;
		player2Character = categoryToString(currentCpuCharacter);
		stringArray = getStrings(currentCpuCharacter);

		std::vector<std::string> commands = characterCommands.getCommands(currentCpuCharacter, selectedCategory);
		if (commands.size() >= 1) {
			selectedCommand = commands[0];
		}

		playerToSelect = -1;
	}

	return updated;

}

std::string Model::categoryToString(std::string category) {
	category.erase(std::remove(category.begin(), category.end(), '['), category.end());
	category.erase(std::remove(category.begin(), category.end(), ']'), category.end());

	return category;
}

void Model::selectNextCategory()
{
	selectedCategory = characterCommands.getNextCategory(currentCpuCharacter, selectedCategory);
	selectedCommand = characterCommands.getCommands(currentCpuCharacter, selectedCategory)[0];
}

void Model::selectPreviousCategory()
{
	selectedCategory = characterCommands.getPreviousCategory(currentCpuCharacter, selectedCategory);
	selectedCommand = characterCommands.getCommands(currentCpuCharacter, selectedCategory)[0];
}

void Model::selectNextCommand()
{
	selectedCommand = characterCommands.getNextCommand(currentCpuCharacter, selectedCategory, selectedCommand);
}

void Model::selectPreviousCommand()
{
	selectedCommand = characterCommands.getPreviousCommand(currentCpuCharacter, selectedCategory, selectedCommand);
}

void Model::toggleSelectedCommand()
{
	const std::string index = currentCpuCharacter + selectedCategory + selectedCommand;

	if (selectedStrings.count(index)) {
		selectedStrings[index] = !selectedStrings[index];
	}
	else {
		selectedStrings[index] = true;
	}
}

bool Model::isSelectedCommand(const std::string command)
{
	const std::string index = currentCpuCharacter + selectedCategory + command;
	return selectedStrings.count(index) && selectedStrings[index];
}

void Model::setToDefaltCategory()
{
	selectedCategory = characterCommands.getCategories(currentCpuCharacter)[0];
	selectedCommand = characterCommands.getCommands(currentCpuCharacter, selectedCategory)[0];
}

std::string Model::getRandomCommand()
{
	selectedCommand = characterCommands.getRandomCommand(currentCpuCharacter, selectedCategory);
	return selectedCommand;
}