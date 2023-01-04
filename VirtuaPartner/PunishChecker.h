#ifndef PUNISH_CHECKER
#define PUNISH_CHECKER

#include <windows.h>
#include <string>
#include "WindowPixelChecker.h"

#pragma once
class PunishChecker : public WindowPixelChecker
{
public:
	PunishChecker(HWND vfWindow);
	enum class AdvantageClass { NONE, THROW, PUNCH, ELBOW, KNEE };
	AdvantageClass advantageClass;

	virtual byte giveFeedback() = 0 {};
	static void playSuccessSound();
	static void playFailureSound();

protected:
	int frameAdvantage;
	bool maxPunishment = false;
	bool guaranteedDamage = true;
	bool cpuKnockdown = false;
	bool recoversLow;
	bool hitsLow;

	void getAdvantageAmount();
};

#endif