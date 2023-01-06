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
	int frameAdvantage;
	void getAdvantageAmount();
	bool maxPunishment = false;

protected:
	bool guaranteedDamage = true;
	bool cpuKnockdown = false;
	bool recoversLow;
	bool hitsLow;
};

#endif