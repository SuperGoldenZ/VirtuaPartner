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

#include "keyboard.h"
#include "ui.h"

using namespace std;

HWND vfWindow;
HDC dc;

const byte ONE_FRAME = 16;

const int WHITE_R = 255;
const int WHITE_G = 251;
const int WHITE_B = 255;

int struggleType = 0;

std::string category;

//If CPU is on the left side or not
bool leftSide = false;

vector<vector<string>> categories;

vector<string> getStrings(string category) {

	for (int i = 0; i < categories.size(); i++) {
		if (categories[i][0] == category) {
			return categories[i];
		}
	}

	return categories[0];
}
static BOOL CALLBACK focusVfWindow(HWND hWnd, LPARAM lparam) {
	int length = GetWindowTextLength(hWnd);
	char* buffer = new char[length + 1];
	GetWindowTextA(hWnd, buffer, length + 1);
	std::string windowTitle(buffer);
	delete[] buffer;

	// List visible windows with a non-empty title
	if (IsWindowVisible(hWnd) && length != 0 && (windowTitle.find("Virtua Fighter") != std::string::npos)) {
		vfWindow = hWnd;
		dc = GetDC(vfWindow);
		std::cout << hWnd << ": " << windowTitle << std::endl;
	}

	return TRUE;
}

bool checkPoint(int x, int y, int r, int g, int b)
{
	const COLORREF color = GetPixel(dc, x, y);
	RGBTRIPLE rgb;

	rgb.rgbtRed = GetRValue(color);
	rgb.rgbtGreen = GetGValue(color);
	rgb.rgbtBlue = GetBValue(color);

	return ((int)rgb.rgbtRed == r && (int)rgb.rgbtGreen == g && (int)rgb.rgbtBlue == b);
}

bool didPkCounter()
{

	if (!checkPoint(324, 522, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	//Number of hits too lower left corner
	if (!checkPoint(168, 552, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}


	return true;
}

bool didCuffisCounter()
{
	//Number of hits 3 lower right up a bit
	if (!checkPoint(167, 545, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}


	return true;
}

bool didKneeCounter()
{
	//Check blue COUNTER text U lower right
	if (!checkPoint(149, 377, 151, 229, 255)) {
		cout << "\nfailed counter check";
		return false;
	}

	//One hit combo 1 middle lower
	if (!checkPoint(160, 550, WHITE_R, WHITE_G, WHITE_B)) {
		cout << "\nfailed 1 check";
		return false;
	}

	//Hit 31 3
	if (!checkPoint(338, 536, WHITE_R, WHITE_G, WHITE_B)) {
		cout << "\nfailed 3 check";
		return false;
	}

	return true;
}

int getAdvantageAmount()
{
	int x = 331;
	int y = 596;

	for (int x = 291; x <= 331; x++) {
		for (int y = 594; y <= 597; y++) {
			COLORREF color = GetPixel(dc, x, y);
			RGBTRIPLE rgb;

			rgb.rgbtRed = GetRValue(color);
			rgb.rgbtGreen = GetGValue(color);
			rgb.rgbtBlue = GetBValue(color);

			if ((int)rgb.rgbtRed == 255 && (int)rgb.rgbtGreen == 177 && (int)rgb.rgbtBlue == 0) {
				return 18;
			}
			else if ((int)rgb.rgbtRed == 255 && (int)rgb.rgbtGreen == 251 && (int)rgb.rgbtBlue == 0) {
				return 15;
			}
			else if ((int)rgb.rgbtRed == 120 && (int)rgb.rgbtGreen == 251 && (int)rgb.rgbtBlue == 120) {
				return 10;
			}
			else if ((int)rgb.rgbtRed == 170 && (int)rgb.rgbtGreen == 251 && (int)rgb.rgbtBlue == 255) {
				return 12;
			}
			else if ((int)rgb.rgbtRed == 67 && (int)rgb.rgbtGreen == 98 && (int)rgb.rgbtBlue == 100) {
				return 13;
			}
		}
	}

	return -1;
}

void executeCommandString(std::string str, bool defense = false, size_t loopCount = 1, int sleepCount = ONE_FRAME) {
	bool executeNext = false;
	liftAllKeys();

	Sleep(sleepCount * 6);

	if (defense == true) {
		keybd_event(KEYS['G'], 0, 0, 0);
		std::cout << " Holding Guard (";
	}

	for (size_t loop = 0; loop < loopCount; loop++) {
		for (size_t i = 0; i < str.size(); i++) {
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

	liftAllKeys();

	int advantageAmount = -1;
	if (defense == true) {
		Sleep(500);
		keybd_event(KEYS['G'], 0, KEYEVENTF_KEYUP, 0);
		std::cout << " )";
	}
	else {
		keybd_event(KEYS['G'], 0, 0, 0);
		std::cout << " G...";
		advantageAmount = getAdvantageAmount();
		Sleep(250);
		Sleep(250);
		if (advantageAmount == -1) {
			advantageAmount = getAdvantageAmount();
		}
		Sleep(250);
		Sleep(250);
		Sleep(250);
		if (advantageAmount == -1) {
			advantageAmount = getAdvantageAmount();
		}

		switch (advantageAmount) {
		case 12:
			cout << "\n\tchecking PK counter - ";
			if (didPkCounter()) {
				cout << "good !";
			}
			else {
				cout << "bad";
			}
			break;
		case 15:
			//Add delay since cuffis takes longer to execute
			Sleep(250);
			cout << "\n\tchecking cuffis counter - ";
			if (didCuffisCounter()) {
				cout << "good !";
			}
			else {
				cout << "bad";
			}
			break;
		case 18:
			cout << "\n\tchecking knee counter - ";
			if (didKneeCounter()) {
				cout << "good !";
			}
			else {
				cout << "bad";
			}
			break;
		default:
			cout << "\n\tunknown advantage" << advantageAmount;
		}

		Sleep(1000);

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
	std::string s;

	if (file.is_open()) {
		while (file.good()) {
			file >> s;
			if (s[0] != '#' && !s.empty()) {
				strings.push_back(s);
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

int main()
{
	srand(time(NULL));
	EnumWindows(focusVfWindow, NULL);

	int waitIndex = 0;
	while (!vfWindow) {
		clear_screen();
		std::cout << "Searching for \"Virtua Fighter\" window. Please start game in a window containing \"Virtua Fighter\" text" << std::endl;
		std::cout << WAIT_CHARACTERS[waitIndex++] << std::endl;

		if (waitIndex == WAIT_CHARACTERS.size()) {
			waitIndex = 0;
		}

		Sleep(250);
		EnumWindows(focusVfWindow, NULL);
	}

	bool randomMode = false;
	bool repeat = false;
	bool random = false;

	vector<string> stringArray;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	loadConfigFiles();

	category = categories[0][0];
	stringArray = getStrings(category);

	int stringIndex = 1;

	printMenu(categories, stringArray[stringIndex], leftSide, category);

	while (true) {
		if (random) {
			stringIndex = rand() % stringArray.size();

			printMenu(categories, stringArray[stringIndex], leftSide, category);
			std::cout << std::endl << "Random string #" << stringIndex << " / " << stringArray.size() << std::endl;
		}

		if (GetAsyncKeyState(VK_1) != 0) {
			while (GetAsyncKeyState(VK_1) != 0);
			leftSide = false;
			printMenu(categories, stringArray[stringIndex], leftSide, category);
		}
		if (GetAsyncKeyState(VK_2) != 0) {
			while (GetAsyncKeyState(VK_2) != 0);
			leftSide = true;
			printMenu(categories, stringArray[stringIndex], leftSide, category);
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
		}

		if (GetAsyncKeyState(VK_ADD) != 0) {
			while (GetAsyncKeyState(VK_ADD) != 0);
			if (stringIndex < stringArray.size() - 1) {
				printMenu(categories, stringArray[++stringIndex], leftSide, category);
			}
		}
		else if (GetAsyncKeyState(VK_SUBTRACT) != 0 && stringIndex > 0) {
			while (GetAsyncKeyState(VK_SUBTRACT) != 0);
			if (stringIndex > 1) {
				printMenu(categories, stringArray[--stringIndex], leftSide, category);
			}
		}

		for (int i = 0; i < categories.size(); i++) {
			byte shortcutKeycote = getKeyEventCode(categories[i][0]);
			if (GetAsyncKeyState(shortcutKeycote) != 0) {
				while (GetAsyncKeyState(shortcutKeycote) != 0);
				category = categories[i][0];
				stringArray = getStrings(category);
				stringIndex = 1;
				printMenu(categories, stringArray[stringIndex], leftSide, category);
				break;
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD1) != 0 || repeat) {
			while (GetAsyncKeyState(VK_NUMPAD1) != 0);
			if (category == "[D]efense") {
				executeCommandString(stringArray[stringIndex], true, 8, 1);
			}
			else {
				executeCommandString(stringArray[stringIndex]);
			}

			printMenu(categories, stringArray[stringIndex], leftSide, category);
		}

		Sleep(ONE_FRAME);

		if (GetAsyncKeyState(VK_ESCAPE) != 0) {
			return 0;
			break;
		}

		loadConfigFiles();
		stringArray = getStrings(category);
	}


	std::cout << " Done " << std::endl;
}