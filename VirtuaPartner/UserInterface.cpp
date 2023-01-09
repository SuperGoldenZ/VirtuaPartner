#include <iostream>

#include <windows.h>
#include <stdio.h>
#include <map>
#include <string>
#include <tchar.h>

#include "UserInterface.h"
#include "PunishStats.h"

UserInterface::UserInterface()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void UserInterface::clear_screen() {
	const char FILL = ' ';

	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, FILL, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

int UserInterface::getColor(bool selected)
{
	if (selected) return 14;

	return 7;
}

void UserInterface::printCharacterName(std::string name, bool selected)
{
	printCharacterName(name, selected, 0, 10);
}

void UserInterface::printCharacterName(std::string name, bool selected, int numEndline)
{
	for (int i = 0; i < name.size(); i++) {
		if (i > 0 && name[i - 1] == '[') {
			SetConsoleTextAttribute(hConsole, 15);
		}
		else {
			SetConsoleTextAttribute(hConsole, getColor(selected));
		}
		std::cout << name[i];
	}


	//Set to default non selected color
	SetConsoleTextAttribute(hConsole, getColor(false));

	if (numEndline == 0) {
		for (int i = name.length(); i <= 10; i++) {
			std::cout << " ";
		}
	}

	for (int i = 0; i < numEndline; i++) {
		std::cout << std::endl;
	}
}

void UserInterface::printCharacterName(std::string name, bool selected, int numEndline, int widthToPrint)
{
	for (int i = 0; i < name.size(); i++) {
		if (i > 0 && name[i - 1] == '[') {
			SetConsoleTextAttribute(hConsole, 15);
		}
		else {
			SetConsoleTextAttribute(hConsole, getColor(selected));
		}
		std::cout << name[i];
	}


	//Set to default non selected color
	SetConsoleTextAttribute(hConsole, getColor(false));

	if (numEndline == 0) {
		for (int i = name.length(); i <= widthToPrint; i++) {
			std::cout << " ";
		}
	}

	for (int i = 0; i < numEndline; i++) {
		std::cout << std::endl;
	}
}

void UserInterface::printMenu(std::vector<std::vector<std::string>> categories, std::string str, bool leftSide, std::string currentCategory, bool punishCheck, std::map<std::string, PunishStats> punishStats, std::map<std::string, bool> selectedStrings, std::string player1CharacterName, int playerToSelect, std::string player2CharacterName)
{
	clear_screen();
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << "Virtua ";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "Partner ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "(alpha 4)" << std::endl;
	std::cout << "-----------------------" << std::endl;

	std::cout << "Player side: ";
	printCharacterName("[1] Left Side", !leftSide, 0, 25);
	printCharacterName("[2] Right Side", leftSide, 1);

	if (punishCheck) {
		printCharacterName("Player char: " + player1CharacterName, false, 0, 38);
	}
	else {
		printCharacterName("Player char: Any", false, 0, 38);
	}

	printCharacterName("CPU Char: " + player2CharacterName, false, 1);
	printCharacterName("TAB to select CPU character manually", false, 1);

	if (player1CharacterName != "") {
		printCharacterName("P[u]nish Check", punishCheck, 2);
	}

	int currentCategoryIndex = -1;
	for (int i = 0; i < categories.size(); i++) {
		if (categories[i][0] == currentCategory) {
			currentCategoryIndex = i;
			break;
		}
	}

	if (currentCategoryIndex == -1) {
		return;
	}

	int lineNumber = 0;
	int moveNumber = 1;
	int i = 0;
	SetConsoleTextAttribute(hConsole, 112);
	if (playerToSelect == -1) {
		std::cout << "CPU Char Commands: " << std::endl;
	}
	else {
		std::cout << "Select player " << playerToSelect << " " << std::endl;
	}

	while ((i < categories.size() || moveNumber < categories[currentCategoryIndex].size()) && (player2CharacterName != "" || playerToSelect == 2)) {
		if (i < categories.size()) {
			if (playerToSelect == 2) {
				printCharacterName(categories[i][0], currentCategory == categories[i][0], 0);
			}
			i++;
		}
		else {
			for (int j = 0; j <= 10; j++) {
				std::cout << " ";
			}
		}

		// Print moves on the right side
		if (moveNumber < categories[currentCategoryIndex].size()) {
			std::string statsIndex = categories[currentCategoryIndex][0] + categories[currentCategoryIndex][moveNumber];

			if (playerToSelect == -1) {
				if (punishCheck) {
					if (selectedStrings[statsIndex]) {
						std::cout << "*";
					}
					else {
						std::cout << " ";
					}
					printCharacterName(
						categories[currentCategoryIndex][moveNumber],
						str == categories[currentCategoryIndex][moveNumber],
						0,
						35);
					std::cout << punishStats[statsIndex].toString();
				}
				else {
					std::cout << " ";
					printCharacterName(categories[currentCategoryIndex][moveNumber], str == categories[currentCategoryIndex][moveNumber], -1);
				}
			}

			moveNumber++;
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	SetConsoleTextAttribute(hConsole, 112);
	std::cout << "NumPad Controls: " << std::endl;

	printCharacterName("[+] Next String", false, 0, 35);
	printCharacterName("[-] Prev String", false, 1);

	printCharacterName("", false, 0, 35);
	printCharacterName("[*] Toggle favorite", false, 1);

	printCharacterName("[1] Play selected", false, 0, 35);
	printCharacterName("[/] Play favorite (random)", false, 1);

	printCharacterName("[0] Start repeat (cur selected)", false, 0, 35);
	printCharacterName("[.] Start repeat (favorites)", false, 1);

	printCharacterName("[2] Start repeat (all)", false, 0, 35);
	printCharacterName("[3] Stop repeat", false, 0, 35);

	std::cout << std::endl;
	std::cout << "? ";
}

void UserInterface::printStrings(const std::vector<std::string> strings) {
	for (int i = 0; i < strings.size(); i++) {
		std::cout << strings[i] << std::endl;
	}
}

void UserInterface::showWaitingScreen()
{
	clear_screen();
	std::cout << "Searching for \"Virtua Fighter\" window.\nPlease start game in a window containing \"Virtua Fighter\" and \"Vulkan\" text" << std::endl;
	std::cout << WAIT_CHARACTERS[waitIndex++] << std::endl;

	if (waitIndex == WAIT_CHARACTERS.size()) {
		waitIndex = 0;
	}
}