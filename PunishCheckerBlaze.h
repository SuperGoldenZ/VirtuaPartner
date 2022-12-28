#ifndef PUNISH_CHECKER_BLAZE
#define PUNISH_CHECKER_BLAZE

#include "PunishChecker.h"

class PunishCheckerBlaze : public PunishChecker
{
private:
	HWND _virtuaFighterWindow;
		
	bool didThrowCounter();
	bool didPkCounter();
	bool didCuffisCounter();
	bool didKneeCounter();
	bool didElbowCounter();
	bool didShadowHammerCounter();
	bool checkPoint(int x, int y, int r, int g, int b);	
	void judgePunishment();
	void makeOpponentPunch();
public:
	PunishCheckerBlaze(HWND virtuaFighterWindow, bool recoversLow, bool hitsLow);
	virtual byte giveFeedback();
};

#endif