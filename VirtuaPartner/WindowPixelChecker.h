#ifndef WINDOW_PUNISH_CHECKER
#define WINDOW_PUNISH_CHECKER

#include <windows.h>
#include <string>

#pragma once
class WindowPixelChecker
{
protected:

public:
	WindowPixelChecker(HWND virtuaFighterWindow);
	bool checkPoint(const int x, const int y, const int r, const int g, const int b);	
	HDC dc;
	HWND _virtuaFighterWindow;
	std::string getSelectedPlayer(int playerNum);

	const int WHITE_R = 255;
	const int WHITE_G = 251;
	const int WHITE_B = 255;

};

#endif