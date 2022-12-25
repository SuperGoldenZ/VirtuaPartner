#include <iostream>

#include <windows.h>
#include <stdio.h>

#include "UserInterface.h"
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
	printCharacterName(name, selected, 0);
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

void UserInterface::printMenu(std::vector<std::vector<std::string>> categories, std::string str, bool leftSide, std::string currentCategory)
{
	clear_screen();
	std::cout << "Virtua Partner (alpha 2)" << std::endl;
	std::cout << "-----------------------" << std::endl;

	printCharacterName("[1] Left Side", !leftSide, 0);
	printCharacterName("[2] Right Side", leftSide, 2);

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

	while (i < categories.size() || moveNumber < categories[currentCategoryIndex].size()) {
		if (i < categories.size()) {
			printCharacterName(categories[i][0], currentCategory == categories[i][0], 0);
			i++;
		}
		else {
			for (int j = 0; j <= 10; j++) {
				std::cout << " ";
			}
		}

		if (moveNumber < categories[currentCategoryIndex].size()) {
			printCharacterName(categories[currentCategoryIndex][moveNumber], str == categories[currentCategoryIndex][moveNumber], -1);
			moveNumber++;
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	printCharacterName("[+] Next String", false, false);
	printCharacterName("[-] Prev String", false, 1);
	printCharacterName("[1] Play string one time", false, 1);
	printCharacterName("[0] Start repeat", false, 1);
	printCharacterName("[2] Start random repeat", false, 1);
	printCharacterName("[3] Stop repeat", false, 1);

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
	std::cout << "Searching for \"Virtua Fighter\" window. Please start game in a window containing \"Virtua Fighter\" text" << std::endl;
	std::cout << WAIT_CHARACTERS[waitIndex++] << std::endl;

	if (waitIndex == WAIT_CHARACTERS.size()) {
		waitIndex = 0;
	}
}