#ifndef PUNISH_CHECKER_BLAZE
#define PUNISH_CHECKER_BLAZE

#include "PunishChecker.h"

class PunishCheckerBlaze : public PunishChecker
{
private:
	bool didThrowCounter();
	bool didPkCounter();
	bool didCuffisCounter();
	bool didKneeCounter();
	bool didElbowCounter();
	bool didShadowHammerCounter();
	void judgePunishment();
	void makeOpponentPunch();
public:
	PunishCheckerBlaze(HWND virtuaFighterWindow, bool recoversLow, bool hitsLow);
	virtual byte giveFeedback();
};

#endif