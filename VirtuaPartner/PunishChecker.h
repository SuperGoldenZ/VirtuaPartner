#ifndef PUNISH_CHECKER
#define PUNISH_CHECKER

#include <windows.h>
#include <string>

#pragma once
class PunishChecker
{
public:
	enum class AdvantageClass { NONE, THROW, PUNCH, ELBOW, KNEE };
	AdvantageClass advantageClass;

	bool checkPoint(int x, int y, int r, int g, int b);
	static bool checkPoint(HWND virtuaFighterWindow, int x, int y, int r, int g, int b);
	virtual byte giveFeedback() = 0 {};
	static void playSuccessSound();
	static void playFailureSound();
	static std::string getSelectedPlayer1(HWND virtuaFighterWindow);

protected:
	const int WHITE_R = 255;
	const int WHITE_G = 251;
	const int WHITE_B = 255;
	HDC dc;
	HWND _virtuaFighterWindow;

	int frameAdvantage;
	bool maxPunishment = false;
	bool guaranteedDamage = true;
	bool cpuKnockdown = false;
	bool recoversLow;
	bool hitsLow;

	void getAdvantageAmount();
};

#endif