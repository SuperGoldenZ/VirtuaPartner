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

#include "akira.h"
#include "aoi.h"
#include "lau.h"
#include "jeffry.h"
#include "defense.h"


HWND vfWindow;

const byte ONE_FRAME = 16;
const byte VK_G = 0x47;
const byte VK_P = 0x50;
const byte VK_K = 0x4B;
const byte VK_A = 0x41;
const byte VK_D = 0x44;
const byte VK_W = 0x57;
const byte VK_S = 0x53;
const byte VK_L = 0x4C;
const byte VK_R = 0x52;
const byte VK_1 = 0x31;
const byte VK_2 = 0x32;
const byte VK_O = 0x4F;

int struggleType = 0;

enum class Categories { Akira, Lau, Defense, Jeffry, Aoi };

HANDLE hConsole;
Categories category = Categories::Akira;

bool leftSide = true;

static BOOL CALLBACK focusVfWindow(HWND hWnd, LPARAM lparam) {
	int length = GetWindowTextLength(hWnd);
	char* buffer = new char[length + 1];
	GetWindowTextA(hWnd, buffer, length + 1);
	std::string windowTitle(buffer);
	delete[] buffer;

	// List visible windows with a non-empty title
	if (IsWindowVisible(hWnd) && length != 0 && (windowTitle.find("Virtua Fighter") != std::string::npos)) {
		vfWindow = hWnd;
		std::cout << hWnd << ": " << windowTitle << std::endl;
	}

	return TRUE;
}

void liftAllKeys(bool defense = false)
{
	keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_W, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_S, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_D, 0, KEYEVENTF_KEYUP, 0);

	if (defense == false) {
		keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	}

	while (GetAsyncKeyState(VK_D) != 0);
	while (GetAsyncKeyState(VK_A) != 0);

}

void executeCommandString(std::string str, bool defense = false, size_t loopCount = 1, int sleepCount = ONE_FRAME) {
	bool executeNext = false;
	liftAllKeys();

	Sleep(sleepCount * 6);

	if (defense == true) {
		keybd_event(VK_G, 0, 0, 0);
		std::cout << " Holding Guard (";
	}

	for (size_t loop = 0; loop < loopCount; loop++) {
		for (size_t i = 0; i < str.size(); i++) {
			if (i <= str.size() - 1 && str[i] == '!') {
				std::cout << "!";
				Sleep(3);
				keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
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

				if (i > 0 && str[i - 1] != '_' && defense == false) {
					Sleep(sleepCount * 10);
				}
			}

			switch (str[i]) {
			case '+':
				executeNext = false;
				std::cout << "+";
				break;
			case 'P':
				keybd_event(VK_P, 0, 0, 0);
				executeNext = true;
				std::cout << "P";
				break;
			case 'K':
				keybd_event(VK_K, 0, 0, 0);
				std::cout << "K";
				executeNext = true;
				break;
			case 'G':
				keybd_event(VK_G, 0, 0, 0);
				std::cout << "G";
				executeNext = true;
				break;
			case '4':
				if (leftSide) {
					keybd_event(VK_A, 0, 0, 0);
				}
				else {
					keybd_event(VK_D, 0, 0, 0);
				}
				std::cout << "4";
				executeNext = true;
				break;
			case '6':
				if (leftSide) {
					keybd_event(VK_D, 0, 0, 0);
				}
				else {
					keybd_event(VK_A, 0, 0, 0);
				}
				std::cout << "6";
				executeNext = true;
				break;
			case '2':
				keybd_event(VK_S, 0, 0, 0);
				std::cout << "2";
				executeNext = true;
				break;
			case '8':
				keybd_event(VK_W, 0, 0, 0);
				std::cout << "8";
				executeNext = true;
				break;
			case '7':
				if (leftSide) {
					keybd_event(VK_A, 0, 0, 0);
				}
				else {
					keybd_event(VK_D, 0, 0, 0);
				}

				keybd_event(VK_W, 0, 0, 0);
				std::cout << "7";
				executeNext = true;
				break;
			case '3':
				if (leftSide) {
					keybd_event(VK_D, 0, 0, 0);
				}
				else {
					keybd_event(VK_A, 0, 0, 0);
				}

				keybd_event(VK_S, 0, 0, 0);
				std::cout << "3";
				executeNext = true;
				break;
			case '1':
				if (leftSide) {
					keybd_event(VK_A, 0, 0, 0);
				}
				else {
					keybd_event(VK_D, 0, 0, 0);
				}

				keybd_event(VK_S, 0, 0, 0);
				std::cout << "1";
				executeNext = true;
				break;
			case '9':
				if (leftSide) {
					keybd_event(VK_D, 0, 0, 0);
				}
				else {
					keybd_event(VK_A, 0, 0, 0);
				}

				keybd_event(VK_W, 0, 0, 0);
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

	if (defense == true) {
		Sleep(500);
		keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
		std::cout << " )";
	}
	else {
		keybd_event(VK_G, 0, 0, 0);
		std::cout << " G...";
		Sleep(1250);
		keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	}


	std::cout << std::endl;
}

void clear_screen(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

int getColor(bool selected)
{
	if (selected) return 14;

	return 7;
}

void printCharacterName(std::string name, bool selected, int numEndline = 0)
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
		std::cout << " ";
	}

	for (int i = 0; i < numEndline; i++) {
		std::cout << std::endl;
	}
}

void printMenu(std::string str = "")
{
	clear_screen();
	std::cout << "Virtua Partner (alpha 1)" << std::endl;
	std::cout << "-----------------------" << std::endl;

	printCharacterName("[1] Left Side", !leftSide, 0);
	printCharacterName("[2] Right Side", leftSide, 2);
	printCharacterName("[A]kira", category == Categories::Akira);
	printCharacterName("A[o]i", category == Categories::Aoi);
	printCharacterName("[L]au", category == Categories::Lau);
	printCharacterName("Jeff[r]y", category == Categories::Jeffry);
	printCharacterName("[D]efense", category == Categories::Defense, 2);

	std::cout << str << std::endl;
	printCharacterName("[+] Next String", false, false);
	printCharacterName("[-] Prev String", false, 1);
	printCharacterName("[1] Play string one time", false, 1);
	printCharacterName("[0] Start repeat", false, 1);
	printCharacterName("[2] Start random repeat", false, 1);
	printCharacterName("[3] Stop repeat", false, 1);

	std::cout << "? ";
}

const std::string* getStrings() {
	switch (category) {
	case Categories::Akira:
		return akira_strings;
	case Categories::Lau:
		return lau_strings;
	}

	if (category == Categories::Defense) {
		return struggle_strings;
	}

	if (category == Categories::Jeffry) {
		return jeffry_strings;
	}

	if (category == Categories::Aoi) {
		return aoi_strings;
	}

	return 0;
}

int main()
{
	srand(time(NULL));
	EnumWindows(focusVfWindow, NULL);
	while (!vfWindow) {
		std::cout << ".";
	}

	int stringIndex = 0;
	bool randomMode = false;
	bool repeat = false;
	bool random = false;

	const std::string* stringArray;

	stringArray = getStrings();

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	printMenu(stringArray[stringIndex]);

	while (true) {
		if (random) {
			stringIndex = rand() % sizeof(stringArray);

			printMenu(stringArray[stringIndex]);
		}

		if (GetAsyncKeyState(VK_1) != 0) {
			while (GetAsyncKeyState(VK_1) != 0);
			leftSide = false;
			printMenu(stringArray[stringIndex]);
		}
		if (GetAsyncKeyState(VK_2) != 0) {
			while (GetAsyncKeyState(VK_2) != 0);
			leftSide = true;
			printMenu(stringArray[stringIndex]);
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
			printMenu(stringArray[++stringIndex]);
		}
		else if (GetAsyncKeyState(VK_SUBTRACT) != 0 && stringIndex > 0) {
			while (GetAsyncKeyState(VK_SUBTRACT) != 0);
			printMenu(stringArray[--stringIndex]);
		}
		else if (GetAsyncKeyState(VK_O) != 0) {
			while (GetAsyncKeyState(VK_O) != 0);
			category = Categories::Aoi;
			stringArray = getStrings();
			stringIndex = 0;
			printMenu(stringArray[stringIndex]);
		}
		else if (GetAsyncKeyState(VK_A) != 0) {
			while (GetAsyncKeyState(VK_A) != 0);
			category = Categories::Akira;
			stringArray = getStrings();
			stringIndex = 0;
			printMenu(stringArray[stringIndex]);
		}
		else if (GetAsyncKeyState(VK_D) != 0) {
			while (GetAsyncKeyState(VK_D) != 0);
			category = Categories::Defense;
			stringArray = getStrings();
			stringIndex = 0;
			printMenu(stringArray[stringIndex]);
		}
		else if (GetAsyncKeyState(VK_L) != 0) {
			while (GetAsyncKeyState(VK_L) != 0);
			category = Categories::Lau;
			stringArray = getStrings();
			stringIndex = 0;
			printMenu(stringArray[stringIndex]);
		}
		else if (GetAsyncKeyState(VK_R) != 0) {
			while (GetAsyncKeyState(VK_R) != 0);
			category = Categories::Jeffry;
			stringArray = getStrings();
			stringIndex = 0;
			printMenu(stringArray[stringIndex]);
		}
		else if (GetAsyncKeyState(VK_NUMPAD1) != 0 || repeat) {
			while (GetAsyncKeyState(VK_NUMPAD1) != 0);
			if (category == Categories::Defense) {
				executeCommandString(stringArray[stringIndex], true, 8, 1);
			}
			else {
				executeCommandString(stringArray[stringIndex]);
			}

			std::cout << "? ";
		}


		Sleep(ONE_FRAME);

		if (GetAsyncKeyState(VK_ESCAPE) != 0) {
			return 0;
			break;
		}
	}


	std::cout << " Done " << std::endl;

}