#include <iostream>

#include <windows.h>
#include <stdio.h>
#include <map>
#include <string>
#include <tchar.h>

#include "ConsoleView.h"
#include "PunishStats.h"

ConsoleView::ConsoleView()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ConsoleView::clear_screen() {
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

int ConsoleView::getColor(bool selected)
{
	if (selected) return 14;

	return 7;
}

void ConsoleView::printCharacterName(std::string name, bool selected)
{
	printCharacterName(name, selected, 0, 10);
}

void ConsoleView::printCharacterName(std::string name, bool selected, int numEndline)
{
	for (unsigned int i = 0; i < name.size(); i++) {
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

void ConsoleView::printCharacterName(std::string name, bool selected, int numEndline, int widthToPrint)
{
	for (unsigned int i = 0; i < name.size(); i++) {
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

void ConsoleView::printMenu(Model model)
{
	clear_screen();
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << "Virtua ";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "Partner ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "(alpha 5)" << std::endl;
	std::cout << "-----------------------" << std::endl;

	std::cout << "Player side: ";
	printCharacterName("[1] Left Side", !model.leftSide, 0, 25);
	printCharacterName("[2] Right Side", model.leftSide, 1);

	if (model.punishCheck) {
		printCharacterName("Player char: " + model.player1Character, false, 0, 38);
	}
	else {
		printCharacterName("Player char: Any", false, 0, 38);
	}

	printCharacterName("CPU Char: " + model.player2Character, false, 1);
	printCharacterName("TAB to select CPU character manually", false, 1);

	if (model.player1Character != "") {
		printCharacterName("P[u]nish Check", model.punishCheck, 2);
	}

	int currentCategoryIndex = model.getCurrentCategoryIndex();

	if (currentCategoryIndex == -1) {
		return;
	}

	int moveNumber = 1;
	int i = 0;
	SetConsoleTextAttribute(hConsole, 112);
	if (model.playerToSelect == -1) {
		std::cout << "CPU Char Commands: " << std::endl;
	}
	else {
		std::cout << "Select player " << model.playerToSelect << " " << std::endl;
	}

	while ((i < model.allCharacterCpuCommandStrings.size() || moveNumber < model.allCharacterCpuCommandStrings[currentCategoryIndex].size()) && (model.player2Character != "" || model.playerToSelect == 2)) {
		if (i < model.allCharacterCpuCommandStrings.size()) {
			if (model.playerToSelect == 2) {
				printCharacterName(model.allCharacterCpuCommandStrings[i][0],
					model.currentCpuCharacter == model.allCharacterCpuCommandStrings[i][0],
					0);
			}
			i++;
		}
		else {
			for (int j = 0; j <= 10; j++) {
				std::cout << " ";
			}
		}

		// Print moves on the right side
		if (moveNumber < model.allCharacterCpuCommandStrings[currentCategoryIndex].size()) {
			std::string statsIndex = model.allCharacterCpuCommandStrings[currentCategoryIndex][0] + model.allCharacterCpuCommandStrings[currentCategoryIndex][moveNumber];

			if (model.playerToSelect == -1) {
				if (model.punishCheck) {
					if (model.selectedStrings[statsIndex]) {
						std::cout << "*";
					}
					else {
						std::cout << " ";
					}
					if (model.stringIndex < model.stringArray.size() - 1) {
						printCharacterName(
							model.allCharacterCpuCommandStrings[currentCategoryIndex][moveNumber],
							model.stringArray[model.stringIndex] == model.allCharacterCpuCommandStrings[currentCategoryIndex][moveNumber],
							0,
							35);
						std::cout << model.punishStats[statsIndex].toString();
					}
					else {
						std::cout << "invalid stringindex " << model.stringIndex << " " << model.stringArray.size();
					}
				}
				else {
					std::cout << " ";
					printCharacterName(model.allCharacterCpuCommandStrings[currentCategoryIndex][moveNumber], model.stringArray[model.stringIndex] == model.allCharacterCpuCommandStrings[currentCategoryIndex][moveNumber], -1);
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

void ConsoleView::printStrings(const std::vector<std::string> strings) {
	for (int i = 0; i < strings.size(); i++) {
		std::cout << strings[i] << std::endl;
	}
}

void ConsoleView::showWaitingScreen()
{
	clear_screen();
	std::cout << "Searching for \"Virtua Fighter\" window.\nPlease start game in a window containing \"Virtua Fighter\" and \"Vulkan\" text" << std::endl;
	std::cout << WAIT_CHARACTERS[waitIndex++] << std::endl;

	if (waitIndex == WAIT_CHARACTERS.size()) {
		waitIndex = 0;
	}
}