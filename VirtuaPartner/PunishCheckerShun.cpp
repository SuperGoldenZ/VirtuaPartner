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

bool PunishCheckerShun::didKneeCounter()
{
	//One hit combo 1 middle lower
	if (!checkPoint(160, 550, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	//Hit 31 3
	if (!checkPoint(338, 536, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	//Hit 31 3
	if (checkPoint(362, 474, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	if (checkPoint(168, 531, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	if (checkPoint(146, 549, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	//Hit 31 3
	if (!checkPoint(366, 553, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}



	return true;
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

/*
* @todo need to implement this later
*/
bool PunishCheckerShun::didElbowCounter()
{
	if (!checkPoint(330, 473, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	if (!checkPoint(332, 535, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	if (!checkPoint(146, 551, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	if (checkPoint(320, 543, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	/*
	if (!checkPoint(332, 472, WHITE_R, WHITE_G, WHITE_B)) {
	return false;
	}

	if (!checkPoint(375, 460, WHITE_R, WHITE_G, WHITE_B)) {
	return false;
	}

	if (!checkPoint(149, 551, WHITE_R, WHITE_G, WHITE_B)) {
	return false;
	}

	if (!checkPoint(376, 538, WHITE_R, WHITE_G, WHITE_B)) {
	return false;
	}*/

	return true;
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

	return true;
}

bool PunishCheckerShun::did15FrameCounter()
{
	if (!checkPoint(131, 354, 151, 229, 255)) {
		return false;
	}

	if (!checkPoint(374, 461, 255, 255, 255)) {
		return false;
	}

	if (!checkPoint(357, 532, 255, 255, 255)) {
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
		if (did15FrameCounter()) {
			maxPunishment = true;
		}
		break;
		/*
		if (hitsLow) {
			std::cout << "\nchecking shadow hammer\n";
			if (didShadowHammerCounter()) {
				maxPunishment = true;
				cpuKnockdown = true;
			}
		}
		else
			if (!recoversLow) {
				//Check shadow hammer first with faster execution
				if (didShadowHammerCounter()) {
					maxPunishment = true;
					cpuKnockdown = true;
				}
				else {
					//Add delay since cuffis takes longer to execute
					Sleep(250);

					if (didCuffisCounter()) {
						maxPunishment = true;
						cpuKnockdown = true;
					}
				}
			}
			else {
				if (didElbowCounter()) {
					maxPunishment = true;
					cpuKnockdown = true;
				}
			}
		break;*/
	case 18:
		if (didKneeCounter()) {
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