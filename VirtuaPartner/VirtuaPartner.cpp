/*
VirtuaPartner.cpp
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <tchar.h>
#include <fstream>
#include <vector>
#include <filesystem>
#include <thread>
#include <sstream>

#include "keyboard.h"
#include "UserInterface.h"
#include "PunishStats.h"
#include "WindowPixelChecker.h"
#include "PunishCheckerBlaze.h"
#include "PunishCheckerShun.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

HWND vfWindow;

const byte ONE_FRAME = 16;

int struggleType = 0;

std::string category;

std::string player1Character;

//If CPU is on the left side or not
bool leftSide = false;

//Whether to give feedback on guaranteed punish damage or not
bool punishCheck = true;

vector<vector<string>> categories;
UserInterface ui;

std::map<string, PunishStats> punishStats;
std::map<string, bool> selectedStrings;

vector<string> getStrings(string category) {

	for (int i = 0; i < categories.size(); i++) {
		if (categories[i][0] == category) {
			return categories[i];
		}
	}

	return categories[0];
}

bool isVirtuaFighterGameWindow(HWND hWnd)
{
	int length = GetWindowTextLength(hWnd);
	char* buffer = new char[length + 1];
	GetWindowTextA(hWnd, buffer, length + 1);
	std::string windowTitle(buffer);
	delete[] buffer;

	if (length == 0) {
		return false;
	}

	if (windowTitle.find("Virtua Fighter 5 Final Showdown") == std::string::npos) {
		return false;
	}

	// Prevent false positives (though limit to emulator like rpc3s & Vulkan)
	if (windowTitle.find("Vulkan") == std::string::npos) {
		return false;
	}

	return true;
}

static BOOL CALLBACK focusVfWindow(HWND hWnd, LPARAM lparam) {
	// Search visible Windows for one running Virtua Fighter
	if (IsWindowVisible(hWnd) && isVirtuaFighterGameWindow(hWnd)) {
		vfWindow = hWnd;
		RECT rect;
		if (GetWindowRect(hWnd, &rect))
		{
			SetWindowPos(hWnd, NULL, rect.left, rect.top, 1296, 759, SWP_NOZORDER);
		}
	}

	return true;
}

void setDefaultConsoleText(int fontSize = 18)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0; // Width of each character in the font
	cfi.dwFontSize.Y = fontSize; // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	system("color 0F");

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 800, 800, TRUE); // 800 width, 100 height
}

void executeCommandString(std::string str, bool defense = false, size_t loopCount = 1, int sleepCount = ONE_FRAME, string statsIndex = "") {
	bool executeNext = false;
	liftAllKeys(false);

	Sleep(sleepCount * 6);

	if (defense == true) {
		keybd_event(KEYS['G'], 0, 0, 0);
		std::cout << " Holding Guard (";
	}

	//Will loop in case of performing defense manuver
	//In case CPU is on offense, loopCount will always be 1
	for (size_t loop = 0; loop < loopCount; loop++) {
		for (size_t i = 0; i < str.size(); i++) {

			//Stop processing if get to end of line comment
			if (str[i] == '#') {
				break;
			}
			if (i <= str.size() - 1 && str[i] == '!') {
				std::cout << "!";
				Sleep(3);
				keybd_event(KEYS['G'], 0, KEYEVENTF_KEYUP, 0);
			}

			//60 / 12 = 5 ms
			if (executeNext == true) {
				std::cout << " ";

				Sleep(sleepCount);

				if (str[i] == '_') {
					std::cout << "_";
				}
				else if (str[i] != '!') {
					liftAllKeys(defense);
				}

				//Double tap in the same direction
				if (i > 0 && str[i] == str[i - 1]) {
					Sleep(sleepCount * 10);
				}
				else if (i > 0 && str[i - 1] != '_' &&
					//Don't delay if in defensive mode
					defense == false &&
					//If moving two directions not in same direction, don't delay
					(str[i] == 'P' || str[i] == 'G' || str[i] == 'K' || str[i] == '5')) {
					Sleep(sleepCount * 10);
				}
			}

			switch (str[i]) {
			case '+':
				executeNext = false;
				std::cout << "+";
				break;
			case 'P':
				keybd_event(KEYS['P'], 0, 0, 0);
				executeNext = true;
				std::cout << "P";
				break;
			case 'K':
				keybd_event(KEYS['K'], 0, 0, 0);
				std::cout << "K";
				executeNext = true;
				break;
			case 'G':
				keybd_event(KEYS['G'], 0, 0, 0);
				std::cout << "G";
				executeNext = true;
				break;
			case '4':
				if (leftSide) {
					keybd_event(KEYS['A'], 0, 0, 0);
				}
				else {
					keybd_event(KEYS['D'], 0, 0, 0);
				}
				std::cout << "4";
				executeNext = true;
				break;
			case '6':
				if (leftSide) {
					keybd_event(KEYS['D'], 0, 0, 0);
				}
				else {
					keybd_event(KEYS['A'], 0, 0, 0);
				}
				std::cout << "6";
				executeNext = true;
				break;
			case '2':
				keybd_event(KEYS['S'], 0, 0, 0);
				std::cout << "2";
				executeNext = true;
				break;
			case '8':
				keybd_event(KEYS['W'], 0, 0, 0);
				std::cout << "8";
				executeNext = true;
				break;
			case '7':
				if (leftSide) {
					keybd_event(KEYS['A'], 0, 0, 0);
				}
				else {
					keybd_event(KEYS['D'], 0, 0, 0);
				}

				keybd_event(KEYS['W'], 0, 0, 0);
				std::cout << "7";
				executeNext = true;
				break;
			case '3':
				if (leftSide) {
					keybd_event(KEYS['D'], 0, 0, 0);
				}
				else {
					keybd_event(KEYS['A'], 0, 0, 0);
				}

				keybd_event(KEYS['S'], 0, 0, 0);
				std::cout << "3";
				executeNext = true;
				break;
			case '1':
				if (leftSide) {
					keybd_event(KEYS['A'], 0, 0, 0);
				}
				else {
					keybd_event(KEYS['D'], 0, 0, 0);
				}

				keybd_event(KEYS['S'], 0, 0, 0);
				std::cout << "1";
				executeNext = true;
				break;
			case '9':
				if (leftSide) {
					keybd_event(KEYS['D'], 0, 0, 0);
				}
				else {
					keybd_event(KEYS['A'], 0, 0, 0);
				}

				keybd_event(KEYS['W'], 0, 0, 0);
				std::cout << "9";
				executeNext = true;
				break;
			case '5':
				std::cout << "5";

				if (defense == false) {
					Sleep(sleepCount);
				}

				break;
			}

			if (i < str.size() - 1 && str[i + 1] == '+') {
				executeNext = false;
			}
		}
	}


	Sleep(sleepCount * 12);

	liftAllKeys(false);

	int advantageAmount = -1;
	if (defense == true) {
		Sleep(500);
		keybd_event(KEYS['G'], 0, KEYEVENTF_KEYUP, 0);
		std::cout << " )";
	}
	else {
		// Don't press guard if throw counterable and checking punish because computer will try to reverse nitaku
		// and hit if you are not fast enough
		if (str.find("#throwcounterable") == std::string::npos || !punishCheck) {
			keybd_event(KEYS['G'], 0, 0, 0);
			std::cout << " G...";
		}

		if (punishCheck) {
			byte result = -1;
			PunishChecker::AdvantageClass advantageClass;

			if (player1Character == "Shun") {
				PunishCheckerShun shun = PunishCheckerShun(vfWindow, str.find("#recoverslow") != std::string::npos, str.find("#hitslow") != std::string::npos);
				result = shun.giveFeedback();
				advantageClass = shun.advantageClass;
			}
			else if (player1Character == "Blaze") {
				PunishCheckerBlaze blaze = PunishCheckerBlaze(vfWindow, str.find("#recoverslow") != std::string::npos, str.find("#hitslow") != std::string::npos);
				result = blaze.giveFeedback();
				advantageClass = blaze.advantageClass;
			}
			else {
				PunishCheckerBlaze blaze = PunishCheckerBlaze(vfWindow, str.find("#recoverslow") != std::string::npos, str.find("#hitslow") != std::string::npos);
				result = blaze.giveFeedback();
				advantageClass = blaze.advantageClass;
			}

			if (result == 0) {
				ui.clear_screen();
				setDefaultConsoleText(82);
				//Red background
				system("color c0");
				switch (advantageClass) {
				case PunishChecker::AdvantageClass::THROW:
					cout << "Missed\nthrow\npunish";
					break;
				case PunishChecker::AdvantageClass::PUNCH:
					cout << "Missed\npunch\npunish";
					break;
				case PunishChecker::AdvantageClass::KNEE:
					cout << "Missed\nknee\npunish";
					break;
				case PunishChecker::AdvantageClass::ELBOW:
					cout << "Missed\nelbow\npunish";
					break;
				}

				punishStats[statsIndex].failureCount++;
				PunishChecker::playFailureSound();
				Sleep(500);
			}
			else if (result == 1) {
				ui.clear_screen();
				setDefaultConsoleText(82);
				//Green background
				system("color a1");
				cout << "MAX\nPUNISH!";
				punishStats[statsIndex].punishCount++;
				PunishChecker::playSuccessSound();
				Sleep(500);
			}
			else {
				cout << "Unknown result?? " << result;
			}
		}

		Sleep(1000);
		system("color 0F");
		setDefaultConsoleText();
		keybd_event(KEYS['G'], 0, KEYEVENTF_KEYUP, 0);
	}

	keybd_event(KEYS['G'], 0, KEYEVENTF_KEYUP, 0);
	while (GetAsyncKeyState(KEYS['G']) != 0);

	std::cout << std::endl;
}

std::vector<std::string> readFile(string filename)
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

void loadConfigFiles()
{
	categories.clear();

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;

	hFind = FindFirstFile(_T("configs\\*"), &ffd);
	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			string configFile;
			configFile += "configs\\";
			wstring wFileName(ffd.cFileName);
			string filename(wFileName.begin(), wFileName.end());

			configFile += filename;
			categories.push_back(readFile(configFile));
		}
	} while (FindNextFile(hFind, &ffd) != 0);
}

void saveStats()
{
	ofstream outfile;
	outfile.open("stats.csv", ios::out | ios::trunc);

	for (auto const& x : punishStats)
	{
		outfile << x.first << "," << punishStats[x.first].punishCount << "," << punishStats[x.first].failureCount << endl;
	}
	outfile.close();
}

void readStats()
{
	std::vector<std::string> strings;

	std::ifstream file("stats.csv");
	if (!file.good()) {
		return;
	}

	std::string firstLine;

	if (file.is_open()) {
		for (std::string line; getline(file, line);) {
			std::stringstream ss(line);
			string key = "";
			int i = 0;
			PunishStats stats;

			for (std::string field; getline(ss, field, ','); ) {
				switch (i) {
				case 0:
					key = field;
					break;
				case 1:
					stats.punishCount = std::stoi(field);
					break;
				case 2:
					stats.failureCount = std::stoi(field);
					break;
				}
				i++;
			}
			punishStats[key] = stats;
		}
	}
}

int getRandomStarredMove(vector<string> stringArray)
{
	int tempStringIndex;

	//This is very hacky way not to get into infinite loop now if no strings selected
	for (int i = 0; i < 1000; i++) {
		tempStringIndex = (rand() % stringArray.size());
		if (tempStringIndex == 0) {
			tempStringIndex = 1;
		}
		if (selectedStrings[stringArray[0] + stringArray[tempStringIndex]]) {
			return tempStringIndex;
		}
	}


	return -1;
}

bool updateSelectedPlayers(WindowPixelChecker checker)
{
	std::string newPlayer1Character = checker.getSelectedPlayer1();
	if (player1Character != newPlayer1Character && newPlayer1Character != "Unknown") {
		player1Character = newPlayer1Character;
		return true;
	}

	return false;
}

int main()
{
	srand(time(NULL));
	EnumWindows(focusVfWindow, NULL);

	int waitIndex = 0;
	setDefaultConsoleText();

	while (!vfWindow) {
		ui.showWaitingScreen();

		Sleep(250);
		EnumWindows(focusVfWindow, NULL);
	}

	bool randomMode = false;
	bool repeat = false;
	bool random = false;
	bool randomSelectedOnly = false;

	vector<string> stringArray;

	loadConfigFiles();

	category = categories[0][0];
	stringArray = getStrings(category);

	int stringIndex = 1;

	readStats();

	ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);

	const WindowPixelChecker vfChecker(vfWindow);

	while (true) {
		if (random) {
			stringIndex = (rand() % stringArray.size());
			if (stringIndex == 0) {
				stringIndex = 1;
			}
			ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
			std::cout << std::endl << "Random string #" << stringIndex << " / " << (stringArray.size() - 1) << std::endl;
		}
		else if (randomSelectedOnly) {
			int tempStringIndex = getRandomStarredMove(stringArray);

			if (tempStringIndex == -1) {
				repeat = false;
				randomSelectedOnly = false;
			}
			else {
				stringIndex = tempStringIndex;
				ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
			}
		}

		if (GetAsyncKeyState(KEYS['U']) != 0) {
			while (GetAsyncKeyState(KEYS['U']) != 0);
			punishCheck = !punishCheck;
			ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
		}

		if (GetAsyncKeyState(VK_1) != 0) {
			while (GetAsyncKeyState(VK_1) != 0);
			leftSide = false;
			ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
		}
		if (GetAsyncKeyState(VK_2) != 0) {
			while (GetAsyncKeyState(VK_2) != 0);
			leftSide = true;
			ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
		}
		if (GetAsyncKeyState(VK_NUMPAD0) != 0) {
			while (GetAsyncKeyState(VK_NUMPAD0) != 0);
			repeat = true;
		}
		if (GetAsyncKeyState(VK_NUMPAD2) != 0) {
			while (GetAsyncKeyState(VK_NUMPAD2) != 0);
			repeat = true;
			random = true;
		}

		if (GetAsyncKeyState(VK_NUMPAD3) != 0) {
			while (GetAsyncKeyState(VK_NUMPAD3) != 0);
			repeat = false;
			random = false;
			randomSelectedOnly = false;
		}

		if (GetAsyncKeyState(VK_MULTIPLY) != 0) {
			while (GetAsyncKeyState(VK_MULTIPLY) != 0);
			selectedStrings[stringArray[0] + stringArray[stringIndex]] = !selectedStrings[stringArray[0] + stringArray[stringIndex]];
			ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
		}
		else if (GetAsyncKeyState(VK_ADD) != 0) {
			while (GetAsyncKeyState(VK_ADD) != 0);
			if (stringIndex < stringArray.size() - 1) {
				ui.printMenu(categories, stringArray[++stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
			}
		}
		else if (GetAsyncKeyState(VK_SUBTRACT) != 0 && stringIndex > 0) {
			while (GetAsyncKeyState(VK_SUBTRACT) != 0);
			if (stringIndex > 1) {
				ui.printMenu(categories, stringArray[--stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
			}
		}

		for (int i = 0; i < categories.size(); i++) {
			byte shortcutKeycote = getKeyEventCode(categories[i][0]);
			if (GetAsyncKeyState(shortcutKeycote) != 0) {
				while (GetAsyncKeyState(shortcutKeycote) != 0);
				category = categories[i][0];
				stringArray = getStrings(category);
				stringIndex = 1;
				ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
				break;
			}
		}

		if (GetAsyncKeyState(VK_DECIMAL) != 0) {
			while (GetAsyncKeyState(VK_DECIMAL) != 0);
			repeat = true;
			randomSelectedOnly = true;
		}
		else if (GetAsyncKeyState(VK_NUMPAD1) != 0 || repeat || GetAsyncKeyState(VK_DIVIDE)) {
			if (GetAsyncKeyState(VK_DIVIDE)) {
				int tempStringIndex = getRandomStarredMove(stringArray);

				if (tempStringIndex == -1) {
					repeat = false;
					randomSelectedOnly = false;
					continue;
				}
				else {
					stringIndex = tempStringIndex;
					ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
				}
			}

			while (GetAsyncKeyState(VK_NUMPAD1) != 0);
			while (GetAsyncKeyState(VK_DIVIDE) != 0);
			if (category == "[D]efense") {
				executeCommandString(stringArray[stringIndex], true, 8, 1);
			}
			else {
				executeCommandString(stringArray[stringIndex], false, 1, ONE_FRAME, stringArray[0] + stringArray[stringIndex]);
			}

			saveStats();
			ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
		}

		Sleep(ONE_FRAME);

		if (updateSelectedPlayers(vfChecker)) {
			ui.printMenu(categories, stringArray[stringIndex], leftSide, category, punishCheck, punishStats, selectedStrings, player1Character);
		}

		if (GetAsyncKeyState(VK_ESCAPE) != 0) {
			return 0;
			break;
		}

		loadConfigFiles();
		stringArray = getStrings(category);
	}


	std::cout << " Done " << std::endl;
}