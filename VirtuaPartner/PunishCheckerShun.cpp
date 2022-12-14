#include <windows.h>
#include <chrono>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#include "PunishChecker.h"
#include "PunishCheckerShun.h"


PunishCheckerShun::PunishCheckerShun(HWND virtuaFighterWindow, bool recoversLow, bool hitsLow) : PunishChecker(virtuaFighterWindow) {
	this->recoversLow = recoversLow;
	this->hitsLow = hitsLow;
};

bool PunishCheckerShun::didPkCounter()
{

	if (!checkPoint(324, 522, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	//Number of hits too lower left corner
	if (!checkPoint(168, 552, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}


	return true;
}

/**
* @todo fix bug where PPP will also count as positive for Shun counter
*/
bool PunishCheckerShun::didCuffisCounter()
{
	//Number of hits 3 lower right up a bit
	if (!checkPoint(167, 545, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	//Prevent false positive with PPP punish
	if (checkPoint(330, 597, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	return true;
}

bool PunishCheckerShun::did16FrameCounter()
{
	bool eyePoke = true;
	// Check for yellow advantage
	if (!checkPoint(294, 597, 255, 251, 0)) {
		eyePoke = false;
	}

	if (!checkPoint(148, 553, WHITE_R, WHITE_G, WHITE_B)) {
		eyePoke = false;
	}

	bool chowan = true;
	if (!checkPoint(160, 533, WHITE_R, WHITE_G, WHITE_B)) {
		chowan = false;
	}

	if (!checkPoint(160, 533, WHITE_R, WHITE_G, WHITE_B)) {
		chowan = false;
	}

	if (!checkPoint(320, 552, WHITE_R, WHITE_G, WHITE_B)) {
		chowan = false;
	}

	if (!checkPoint(356, 481, WHITE_R, WHITE_G, WHITE_B)) {
		chowan = false;
	}

	if (checkPoint(322, 597, WHITE_R, WHITE_G, WHITE_B)) {
		chowan = false;
	}

	return eyePoke || chowan;
}

bool PunishCheckerShun::did17FrameCounter()
{
	// It's same punishable moves as 18 frame counter
	return did18FrameCounter();
}

bool PunishCheckerShun::did18FrameCounter()
{
	bool muleKick = true;

	// Check for 8K+G
	//Prevent false positive with PPP punish
	if (checkPoint(361, 472, WHITE_R, WHITE_G, WHITE_B)) {
		muleKick = false;
	}

	if (!checkPoint(356, 531, WHITE_R, WHITE_G, WHITE_B)) {
		muleKick = false;
	}

	// Check for yellow advantage, water dragon won't have because it launches
	if (checkPoint(294, 597, 255, 251, 0)) {
		muleKick = false;
	}

	bool waterDragon = true;
	//Prevent false positive with PPP punish
	if (!checkPoint(374, 479, WHITE_R, WHITE_G, WHITE_B)) {
		waterDragon = false;
	}

	if (!checkPoint(337, 547, WHITE_R, WHITE_G, WHITE_B)) {
		waterDragon = false;
	}

	if (!checkPoint(354, 540, WHITE_R, WHITE_G, WHITE_B)) {
		waterDragon = false;
	}

	if (!checkPoint(374, 459, WHITE_R, WHITE_G, WHITE_B)) {
		waterDragon = false;
		muleKick = false;
	}

	if (checkPoint(368, 535, WHITE_R, WHITE_G, WHITE_B)) {
		waterDragon = false;
	}

	// Check for yellow advantage, water dragon won't have because it launches
	if (checkPoint(294, 597, 255, 251, 0)) {
		waterDragon = false;
		muleKick = false;
	}

	return muleKick || waterDragon;
}

/**
* Returns -1 if not found situation for guaranteed punish
* Returns 0 if guaranteed punish situation but not actually punished
* Returns 1 if guaranteed punish situation and punished successfully
*/
byte PunishCheckerShun::giveFeedback() {
	frameAdvantage = -1;

	getAdvantageAmount();

	if (frameAdvantage == -1) {
		return -1;
	}

	judgePunishment();
	if (!guaranteedDamage) {
		return -1;
	}

	if (!maxPunishment) {
		return 0;
	}

	return 1;
}

bool PunishCheckerShun::didThrowCounter()
{
	//Check for +10 green advantage (no action taken while)
	if (checkPoint(293, 595, 120, 251, 120)) {
		return false;
	}

	if (checkPoint(330, 600, 120, 251, 120)) {
		return false;
	}

	if (checkPoint(333, 482, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	if (checkPoint(330, 597, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	if (checkPoint(161, 540, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	if (checkPoint(123, 367, 186, 162, 120)) {
		return false;
	}

	return true;
}

bool PunishCheckerShun::did14FrameCounter()
{
	// Check for blue counter text
	if (!checkPoint(131, 354, 151, 229, 255)) {
		return false;
	}

	if (!checkPoint(158, 538, 255, 255, 255)) {
		return false;
	}

	if (!checkPoint(356, 478, 255, 255, 255)) {
		return false;
	}

	if (!checkPoint(356, 478, 255, 255, 255)) {
		return false;
	}

	if (!checkPoint(318, 545, 255, 255, 255)) {
		return false;
	}


	if (!checkPoint(377, 545, 255, 255, 255)) {
		return false;
	}

	if (checkPoint(362, 490, 255, 255, 255)) {
		return false;
	}

	return true;
}

bool PunishCheckerShun::did15FrameCounter(bool isStanding)
{
	if (isStanding) {
		if (!checkPoint(362, 488, 255, 255, 255)) {
			return false;
		}

		if (checkPoint(328 - 3, 595 - 3, 255, 251, 255)) {
			return false;
		}

		if (!checkPoint(364, 538, 255, 255, 255)) {
			return false;
		}

		return true;
	}

	if (!checkPoint(149, 525, 255, 251, 255)) {
		return false;
	}

	return true;
}

bool PunishCheckerShun::did19FrameCounter()
{
	if (!checkPoint(321, 524, 255, 255, 255)) {
		return false;
	}

	if (checkPoint(363, 538, 255, 255, 255)) {
		return false;
	}

	if (!checkPoint(339, 545, 255, 255, 255)) {
		return false;
	}

	return true;
}

void PunishCheckerShun::judgePunishment()
{
	maxPunishment = false;
	guaranteedDamage = true;
	cpuKnockdown = false;
	std::thread punchThread;

	if (frameAdvantage == 10) {
		punchThread = std::thread([this] {this->makeOpponentPunch(); });
		Sleep(575);
	}
	else {
		Sleep(1000);
	}

	if (frameAdvantage >= 19) {
		if (did19FrameCounter()) {
			maxPunishment = true;
		}
		return;
	}

	switch (frameAdvantage) {
	case 10:
		if (didThrowCounter()) {
			maxPunishment = true;
		}
		break;
	case 12:
		if (didPkCounter()) {
			maxPunishment = true;
		}
		break;
	case 14:
		if (did14FrameCounter()) {
			maxPunishment = true;
		}
		break;

	case 15:
		if (did15FrameCounter(!recoversLow)) {
			maxPunishment = true;
		}
		break;
	case 16:
		if (did16FrameCounter()) {
			maxPunishment = true;
		}
		break;
	case 17:
		if (did17FrameCounter()) {
			maxPunishment = true;
			cpuKnockdown = true;
		}
		break;
	case 18:
		if (did18FrameCounter()) {
			maxPunishment = true;
			cpuKnockdown = true;
		}
		break;
	default:
		guaranteedDamage = false;
	}

	if (frameAdvantage == 10) {
		punchThread.join();
	}
}

/*
* Make opponent try to punch out of throw counterable moves
* Should do async as not to disturb guaranteed punish advantage
* amount check after execution string
*/
void PunishCheckerShun::makeOpponentPunch()
{
	for (int i = 0; i < 6; i++) {
		//@todo don't hardcode punch
		keybd_event(0x50, 0, 0, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		keybd_event(0x50, 0, KEYEVENTF_KEYUP, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}