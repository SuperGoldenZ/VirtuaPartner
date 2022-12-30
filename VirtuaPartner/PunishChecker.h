#ifndef PUNISH_CHECKER
#define PUNISH_CHECKER

#pragma once
class PunishChecker
{
public:
	enum class AdvantageClass { NONE, THROW, PUNCH, ELBOW, KNEE };
	AdvantageClass advantageClass;

	virtual byte giveFeedback() = 0 {};
	static void playSuccessSound();
	static void playFailureSound();	

protected:
	const int WHITE_R = 255;
	const int WHITE_G = 251;
	const int WHITE_B = 255;
	void getAdvantageAmount();
	int frameAdvantage;
	HDC dc;
	bool maxPunishment = false;
	bool guaranteedDamage = true;
	bool cpuKnockdown = false;

	bool recoversLow;
	bool hitsLow;	
};

#endif