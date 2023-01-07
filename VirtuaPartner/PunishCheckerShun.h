#ifndef PUNISH_CHECKER_SHUN
#define PUNISH_CHECKER_SHUN

#include "PunishChecker.h"

class PunishCheckerShun : public PunishChecker
{
private:			
	bool didThrowCounter();
	bool didPkCounter();
	bool didCuffisCounter();	

	// 14 frame counterable moves not so common
	// One such is Eileen P3+PK
	bool did14FrameCounter();
	bool did15FrameCounter(bool isStanding);
	bool did18FrameCounter();
	bool did19FrameCounter();
	void makeOpponentPunch();
public:
	PunishCheckerShun(HWND virtuaFighterWindow, bool recoversLow, bool hitsLow);
	virtual byte giveFeedback();
	void judgePunishment();
};

#endif