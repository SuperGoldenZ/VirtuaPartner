/*
VirtuaPartner.cpp
*/

#include "lau.h"
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <tchar.h>

HWND vfWindow;

const byte ONE_FRAME = 16;
const byte VK_G = 0x47;
const byte VK_P = 0x50;
const byte VK_K = 0x4B;
const byte VK_A = 0x41;
const byte VK_D = 0x44;
const byte VK_W = 0x57;
const byte VK_S = 0x53;

int struggleType = 0;

void struggle_pk(int count)
{
	std::cout << "Struggling" << std::endl;
	keybd_event(VK_G, 0, 0, 0);

	for (int i = 0; i < count; i++) {
		keybd_event(VK_G, 0, 0, 0);
		Sleep(4);
		keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
		Sleep(4);
		keybd_event(VK_K, 0, 0, 0);
		Sleep(4);
		keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
		Sleep(4);
	}

	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << "Struggling DONE" << std::endl;
}

void struggle_left_right_pk(int count, int sleepCount)
{
	std::cout << "Struggling V 46 PK" << std::endl;
	keybd_event(VK_G, 0, 0, 0);

	for (int i = 0; i < count; i++) {
		keybd_event(VK_P, 0, 0, 0);
		keybd_event(VK_A, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);
		Sleep(sleepCount);

		keybd_event(VK_K, 0, 0, 0);
		keybd_event(VK_D, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_D, 0, KEYEVENTF_KEYUP, 0);

		Sleep(sleepCount);
	}

	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << "Struggling DONE" << std::endl;
}

void struggle_left_right_pk_stagger(int count, int sleepCount)
{
	std::cout << "Struggling V 46 PK" << std::endl;
	keybd_event(VK_G, 0, 0, 0);

	for (int i = 0; i < count; i++) {
		keybd_event(VK_P, 0, 0, 0);
		Sleep(sleepCount);
		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);

		keybd_event(VK_A, 0, 0, 0);
		Sleep(sleepCount);
		keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);

		keybd_event(VK_K, 0, 0, 0);
		Sleep(sleepCount);
		keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);

		keybd_event(VK_D, 0, 0, 0);
		Sleep(sleepCount);
		keybd_event(VK_D, 0, KEYEVENTF_KEYUP, 0);
	}

	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << "Struggling DONE" << std::endl;
}

void struggle_left_right_pk_fast(int count, int sleepCount)
{
	std::cout << "Struggling V 46 PK" << std::endl;
	keybd_event(VK_G, 0, 0, 0);

	for (int i = 0; i < count; i++) {
		keybd_event(VK_P, 0, 0, 0);
		keybd_event(VK_A, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_K, 0, 0, 0);
		keybd_event(VK_D, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_D, 0, KEYEVENTF_KEYUP, 0);
	}

	Sleep(500);

	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << "Struggling DONE" << std::endl;
}

void struggle_left_right_pk_together(int count, int sleepCount)
{
	std::cout << "Struggling V 46 PK" << std::endl;
	keybd_event(VK_G, 0, 0, 0);

	for (int i = 0; i < count; i++) {
		keybd_event(VK_P, 0, 0, 0);
		keybd_event(VK_K, 0, 0, 0);
		keybd_event(VK_A, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, 0, 0);
		keybd_event(VK_K, 0, 0, 0);
		keybd_event(VK_D, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_D, 0, KEYEVENTF_KEYUP, 0);

		Sleep(sleepCount);
	}

	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << "Struggling DONE" << std::endl;
}

void struggle_left_right_p(int count, int sleepCount)
{
	std::cout << "Struggling V 46 PK" << std::endl;
	keybd_event(VK_G, 0, 0, 0);

	for (int i = 0; i < count; i++) {
		keybd_event(VK_P, 0, 0, 0);
		keybd_event(VK_A, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, 0, 0);
		keybd_event(VK_D, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_D, 0, KEYEVENTF_KEYUP, 0);

		Sleep(sleepCount);
	}

	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << "Struggling DONE" << std::endl;
}

void struggle_diags_pk(int count, int sleepCount)
{
	std::cout << "Struggling V 46 PK" << std::endl;
	keybd_event(VK_G, 0, 0, 0);

	for (int i = 0; i < count; i++) {
		keybd_event(VK_P, 0, 0, 0);
		keybd_event(VK_A, 0, 0, 0);
		keybd_event(VK_W, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_W, 0, KEYEVENTF_KEYUP, 0);
		Sleep(sleepCount);

		keybd_event(VK_K, 0, 0, 0);
		keybd_event(VK_D, 0, 0, 0);
		keybd_event(VK_S, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_D, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_S, 0, KEYEVENTF_KEYUP, 0);

		Sleep(sleepCount);
	}

	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << "Struggling DONE" << std::endl;
}

void struggle_leftup_pk(int count, int sleepCount)
{
	std::cout << "Struggling V 46 PK" << std::endl;
	keybd_event(VK_G, 0, 0, 0);

	for (int i = 0; i < count; i++) {
		keybd_event(VK_P, 0, 0, 0);
		keybd_event(VK_A, 0, 0, 0);
		keybd_event(VK_W, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_W, 0, KEYEVENTF_KEYUP, 0);
		Sleep(sleepCount);

		keybd_event(VK_A, 0, 0, 0);
		keybd_event(VK_K, 0, 0, 0);
		Sleep(sleepCount);

		keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
		Sleep(sleepCount);
	}

	Sleep(1000);

	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << "Struggling DONE" << std::endl;
}

void struggle_up_down_pk(int count)
{
	std::cout << "Struggling V 46 PK" << std::endl;
	keybd_event(VK_G, 0, 0, 0);

	for (int i = 0; i < count; i++) {
		keybd_event(VK_P, 0, 0, 0);
		keybd_event(VK_W, 0, 0, 0);
		Sleep(4);

		keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_W, 0, KEYEVENTF_KEYUP, 0);
		Sleep(4);

		keybd_event(VK_K, 0, 0, 0);
		keybd_event(VK_S, 0, 0, 0);
		Sleep(4);

		keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_S, 0, KEYEVENTF_KEYUP, 0);

		Sleep(4);
	}

	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << "Struggling DONE" << std::endl;
}

void struggle_left_right(int count)
{
	std::cout << "Struggling V 46" << std::endl;

	//G Key
	keybd_event(0x47, 0, 0, 0);

	int i;
	for (i = 0; i < count; i++) {

		//A
		keybd_event(0x41, 0, 0, 0);

		Sleep(4);

		keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);

		Sleep(4);

		keybd_event(0x44, 0, 0, 0);

		Sleep(4);

		//D
		keybd_event(0x44, 0, KEYEVENTF_KEYUP, 0);

		Sleep(4);
	}

	keybd_event(0x47, 0, KEYEVENTF_KEYUP, 0);

	std::cout << "Struggling DONE" << std::endl;
}

static BOOL CALLBACK focusVfWindow(HWND hWnd, LPARAM lparam) {
	int length = GetWindowTextLength(hWnd);
	char* buffer = new char[length + 1];
	GetWindowTextA(hWnd, buffer, length + 1);
	std::string windowTitle(buffer);
	delete[] buffer;

	// List visible windows with a non-empty title
	if (IsWindowVisible(hWnd) && length != 0 && (windowTitle.find("Virtua Fighter") != std::string::npos)) {
		//vfWindow = hWnd;
		vfWindow = hWnd;
		std::cout << hWnd << ": " << windowTitle << std::endl;


		//if (struggleType == 1) {
		//struggle_left_right_pk(10);
		//}
		//else if (struggleType == 2) {
		//struggle_left_right(15);
		//}
		//else {
		//struggle(10);
		//}
	}

	return TRUE;
}

int mainLoop()
{
	int sleepCount = 4;

	while (true) {
		std::cout << ".";
		if (GetAsyncKeyState(VK_ESCAPE) != 0) {
			return 0;
			break;
		}

		if (GetAsyncKeyState(VK_OEM_PLUS) != 0) {
			std::cout << std::endl << ++sleepCount << std::endl;
		}
		else if (GetAsyncKeyState(VK_OEM_MINUS) != 0) {
			std::cout << std::endl << --sleepCount << std::endl;
		}

		if (GetAsyncKeyState(0x31) != 0) {
			SetForegroundWindow(vfWindow);
			SetActiveWindow(vfWindow);
			SetFocus(vfWindow);
			struggle_left_right_pk(7, sleepCount);
		}


		if (GetAsyncKeyState(0x32) != 0) {
			SetForegroundWindow(vfWindow);
			SetActiveWindow(vfWindow);
			SetFocus(vfWindow);
			struggle_left_right(10);
		}

		if (GetAsyncKeyState(0x33) != 0) {
			SetForegroundWindow(vfWindow);
			SetActiveWindow(vfWindow);
			SetFocus(vfWindow);
			struggle_up_down_pk(7);
		}

		if (GetAsyncKeyState(0x34) != 0) {
			SetForegroundWindow(vfWindow);
			SetActiveWindow(vfWindow);
			SetFocus(vfWindow);
			struggle_diags_pk(7, sleepCount);
		}

		if (GetAsyncKeyState(0x35) != 0) {
			SetForegroundWindow(vfWindow);
			SetActiveWindow(vfWindow);
			SetFocus(vfWindow);
			struggle_leftup_pk(14, sleepCount);
		}

		if (GetAsyncKeyState(0x36) != 0) {
			SetForegroundWindow(vfWindow);
			SetActiveWindow(vfWindow);
			SetFocus(vfWindow);
			struggle_left_right_pk_together(7, sleepCount);
		}

		if (GetAsyncKeyState(0x37) != 0) {
			SetForegroundWindow(vfWindow);
			SetActiveWindow(vfWindow);
			SetFocus(vfWindow);
			struggle_left_right_p(7, sleepCount);
		}

		if (GetAsyncKeyState(0x38) != 0) {
			SetForegroundWindow(vfWindow);
			SetActiveWindow(vfWindow);
			SetFocus(vfWindow);
			struggle_left_right_pk_fast(14, sleepCount);
		}

		if (GetAsyncKeyState(0x39) != 0) {
			SetForegroundWindow(vfWindow);
			SetActiveWindow(vfWindow);
			SetFocus(vfWindow);
			struggle_left_right_pk_stagger(14, sleepCount);
		}


		Sleep(60);
	}

}

void liftAllKeys()
{
	keybd_event(VK_P, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_K, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_W, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_A, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_S, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_D, 0, KEYEVENTF_KEYUP, 0);

}

void executeCommandString(std::string str) {
	bool executeNext = false;
	liftAllKeys();

	Sleep(ONE_FRAME * 6);
	for (int i = 0; i < str.size(); i++) {

		//60 / 12 = 5 ms
		if (executeNext == true) {
			std::cout << " ";
			Sleep(ONE_FRAME);
			if (str[i] == '_') {
				std::cout << "_";
			}
			else {
				liftAllKeys();
			}

			if (i > 0 && str[i - 1] != '_') {
				Sleep(ONE_FRAME * 8);
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
			keybd_event(VK_A, 0, 0, 0);
			std::cout << "4";
			executeNext = true;
			break;
		case '6':
			keybd_event(VK_D, 0, 0, 0);
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
			keybd_event(VK_A, 0, 0, 0);
			keybd_event(VK_W, 0, 0, 0);
			std::cout << "7";
			executeNext = true;
			break;
		case '3':
			keybd_event(VK_D, 0, 0, 0);
			keybd_event(VK_S, 0, 0, 0);
			std::cout << "3";
			executeNext = true;
			break;
		case '9':
			keybd_event(VK_D, 0, 0, 0);
			keybd_event(VK_W, 0, 0, 0);
			std::cout << "9";
			executeNext = true;
			break;
		case '5':
			std::cout << "5";
			Sleep(ONE_FRAME);
			break;
		}

		if (i < str.size() - 1 && str[i + 1] == '+') {
			executeNext = false;
		}
	}

	Sleep(ONE_FRAME * 12);
	liftAllKeys();
	keybd_event(VK_G, 0, 0, 0);
	Sleep(ONE_FRAME * 120);
	keybd_event(VK_G, 0, KEYEVENTF_KEYUP, 0);
	std::cout << std::endl;
}

int main()
{
	std::cout << "Virtua Partner" << std::endl;
	EnumWindows(focusVfWindow, NULL);
	while (!vfWindow) {
		std::cout << ".";
	}

	int stringIndex = 0;
	bool randomMode = false;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "[";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "L";
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "]";
	std::cout << "au" << std::endl;

	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "[";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "+";
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "]";
	std::cout << " Next String" << std::endl;

	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "[";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "-";
	SetConsoleTextAttribute(hConsole, 8);
	std::cout << "]";
	std::cout << " Previous String" << std::endl;

	std::cout << "? ";

	while (true) {
		if (GetAsyncKeyState(VK_ADD) != 0) {
			while (GetAsyncKeyState(VK_ADD) != 0);
			std::cout << std::endl << "New String: " << lau_strings[++stringIndex] << std::endl << "? ";
		}
		else if (GetAsyncKeyState(VK_SUBTRACT) != 0 && stringIndex > 0) {
			while (GetAsyncKeyState(VK_SUBTRACT) != 0);
			std::cout << std::endl << "New Index: " << lau_strings[--stringIndex] << std::endl << "? ";
		}

		if (GetAsyncKeyState(VK_SPACE) != 0) {
			executeCommandString(lau_strings[stringIndex]);
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