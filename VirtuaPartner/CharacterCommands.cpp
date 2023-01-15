#include "CharacterCommands.h"

void CharacterCommands::addCharacterName(const std::string characterName)
{
	characterNames[numCharactersLoaded++] = characterName;
}

void CharacterCommands::addCategoryName(const std::string characterName, const std::string categoryName)
{
	categories[characterName].push_back(categoryName);
}

void CharacterCommands::clear()
{
	numCharactersLoaded = 0;
	categories.clear();
	commands.clear();
}

void CharacterCommands::addCommand(const std::string characterName, const std::string categoryName, const std::string command)
{
	commands[characterName + categoryName].push_back(command);
}

std::vector<std::string> CharacterCommands::getCommands(const std::string characterName, const std::string categoryName) {
	return commands[characterName + categoryName];
}

std::vector<std::string> CharacterCommands::getCategories(const std::string characterName)
{
	return categories[characterName];
}

std::string CharacterCommands::selectNextCaregory(const std::string characterName, const std::string categoryName)
{
	for (unsigned int i = 0; i < categories[characterName].size(); i++) {
		if (categories[characterName][i] == categoryName) {
			if (i < categories[characterName].size() - 1) {
				return categories[characterName][i + 1];
			}

			return categories[characterName][0];
		}
	}
}