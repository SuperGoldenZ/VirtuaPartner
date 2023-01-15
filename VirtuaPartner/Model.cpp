#include "Model.h"

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <cstring>

Model::Model()
{

}

void Model::loadConfigFiles()
{
	categories.clear();

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

			configFile += filename;
			categories.push_back(readFile(configFile));
		}
	} while (FindNextFile(hFind, &ffd) != 0);
}

int Model::getCurrentCategoryIndex()
{
	int currentCategoryIndex = -1;
	for (int i = 0; i < categories.size(); i++) {
		if (categories[i][0] == currentCategory) {
			currentCategoryIndex = i;
			break;
		}
	}

	return currentCategoryIndex;
}

std::vector<std::string> Model::readFile(std::string filename)
{
	std::vector<std::string> strings;

	std::ifstream file(filename);
	std::string firstLine;

	if (file.is_open()) {
		for (std::string line; getline(file, line);) {
			if (line[0] != '#' && !line.empty()) {
				if (!firstLine.empty() && punishStats.find(firstLine + line) == punishStats.end()) {
					punishStats[firstLine + line] = PunishStats();
					selectedStrings[firstLine + line] = false;
				}
				strings.push_back(line);
			}

			if (firstLine.empty()) {
				firstLine = line;
			}
		}
	}

	return strings;
}

std::vector<std::string> Model::getStrings(std::string category) {

	for (unsigned int i = 0; i < categories.size(); i++) {
		if (categories[i][0] == category) {
			return categories[i];
		}
	}

	return categories[0];
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
			currentCategory = "[A]kira";
		}
		else if (player2Character == "Aoi") {
			currentCategory = "A[o]i";
		}
		else if (player2Character == "Blaze") {
			currentCategory = "Bla[z]e";
		}
		else if (player2Character == "Brad") {
			currentCategory = "[B]rad";
		}
		else if (player2Character == "Eileen") {
			currentCategory = "[E]ileen";
		}
		else if (player2Character == "Goh") {
			currentCategory = "[G]oh";
		}
		else if (player2Character == "Jacky") {
			currentCategory = "Ja[c]ky";
		}
		else if (player2Character == "Jean") {
			currentCategory = "[J]ean";
		}
		else if (player2Character == "Jeffry") {
			currentCategory = "Jeff[r]y";
		}
		else if (player2Character == "Lion") {
			currentCategory = "L[i]on";
		}
		else if (player2Character == "Sarah") {
			currentCategory = "[S]arah";
		}
		else if (player2Character == "Lau") {
			currentCategory = "[L]au";
		}
		else if (player2Character == "Kage") {
			currentCategory = "[K]age";
		}
		else if (player2Character == "Lau") {
			currentCategory = "[L]au";
		}
		else if (player2Character == "Pai") {
			currentCategory = "[P]ai";
		}
		else if (player2Character == "Shun") {
			currentCategory = "S[h]un";
		}
		else if (player2Character == "Taka") {
			currentCategory = "[T]aka";
		}
		else if (player2Character == "Vanessa") {
			currentCategory = "[V]anessa";
		}
		else if (player2Character == "Wolf") {
			currentCategory = "[W]olf";
		}
		else if (player2Character == "Lei-Fei") {
			currentCategory = "Lei-[F]ei";
		}

		updated = true;
		player2Character = categoryToString(currentCategory);
		stringArray = getStrings(currentCategory);
		stringIndex = 1;
		playerToSelect = -1;
	}

	return updated;

}

std::string Model::categoryToString(std::string category) {
	category.erase(std::remove(category.begin(), category.end(), '['), category.end());
	category.erase(std::remove(category.begin(), category.end(), ']'), category.end());

	return category;
}