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
	bool did14FrameCounter();
	void makeOpponentPunch();
public:
	PunishCheckerShun(HWND virtuaFighterWindow, bool recoversLow, bool hitsLow);
	virtual byte giveFeedback();
	void judgePunishment();
};

#endif