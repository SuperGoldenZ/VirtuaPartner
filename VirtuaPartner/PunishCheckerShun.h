#ifndef PUNISH_CHECKER_SHUN
#define PUNISH_CHECKER_SHUN

#include "PunishChecker.h"

class PunishCheckerShun : public PunishChecker
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
	PunishCheckerShun(HWND virtuaFighterWindow, bool recoversLow, bool hitsLow);
	virtual byte giveFeedback();
};

#endif