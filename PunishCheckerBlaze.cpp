#include <windows.h>
#include <chrono>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#include "PunishCheckerBlaze.h"

PunishCheckerBlaze::PunishCheckerBlaze(HWND virtuaFighterWindow, bool recoversLow, bool hitsLow) {
	_virtuaFighterWindow = virtuaFighterWindow;
	dc = GetDC(virtuaFighterWindow);
	frameAdvantage = -1;
	this->recoversLow = recoversLow;
	this->hitsLow = hitsLow;
};

bool PunishCheckerBlaze::didPkCounter()
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
* @todo fix bug where PPP will also count as positive for Blaze counter
*/
bool PunishCheckerBlaze::didCuffisCounter()
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

bool PunishCheckerBlaze::didShadowHammerCounter()
{
	if (!checkPoint(331, 477, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	if (checkPoint(329, 597, WHITE_R, WHITE_G, WHITE_B)) {
		return false;
	}

	return true;
}

bool PunishCheckerBlaze::didKneeCounter()
{
	//Check blue COUNTER text U lower right
	if (!checkPoint(149, 377, 151, 229, 255)) {
		return false;
	}

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

bool PunishCheckerBlaze::checkPoint(int x, int y, int r, int g, int b)
{
	const COLORREF color = GetPixel(dc, x, y);
	RGBTRIPLE rgb;

	rgb.rgbtRed = GetRValue(color);
	rgb.rgbtGreen = GetGValue(color);
	rgb.rgbtBlue = GetBValue(color);

	return ((int)rgb.rgbtRed == r && (int)rgb.rgbtGreen == g && (int)rgb.rgbtBlue == b);
}

/**
* Returns -1 if not found situation for guaranteed punish
* Returns 0 if guaranteed punish situation but not actually punished
* Returns 1 if guaranteed punish situation and punished successfully
*/
byte PunishCheckerBlaze::giveFeedback() {
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
bool PunishCheckerBlaze::didElbowCounter()
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

bool PunishCheckerBlaze::didThrowCounter()
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

void PunishCheckerBlaze::judgePunishment()
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
	case 15:
		if (hitsLow) {
			std::cout << "\nchecking shadow hammer\n";
			if (didShadowHammerCounter()) {
				maxPunishment = true;
				cpuKnockdown = true;
			}
		}
		else
			if (!recoversLow) {
				//Add delay since cuffis takes longer to execute
				Sleep(250);

				if (didCuffisCounter()) {
					maxPunishment = true;
					cpuKnockdown = true;
				}
			}
			else {
				if (didElbowCounter()) {
					maxPunishment = true;
					cpuKnockdown = true;
				}
			}
		break;
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

void PunishCheckerBlaze::playSuccessSound()
{
	mciSendString(_T("play success_02.wav"), NULL, 0, NULL);
}

void PunishCheckerBlaze::playFailureSound()
{
	mciSendString(_T("play failed_01.wav"), NULL, 0, NULL);
}

/*
* Make opponent try to punch out of throw counterable moves
* Should do async as not to disturb guaranteed punish advantage
* amount check after execution string
*/
void PunishCheckerBlaze::makeOpponentPunch()
{
	for (int i = 0; i < 6; i++) {
		//@todo don't hardcode punch
		keybd_event(0x50, 0, 0, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		keybd_event(0x50, 0, KEYEVENTF_KEYUP, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void PunishCheckerBlaze::getAdvantageAmount()
{
	for (int i = 0; i < 5; i++) {
		int x = 331;
		int y = 596;

		for (int x = 291; x <= 331; x++) {
			for (int y = 594; y <= 597; y++) {
				COLORREF color = GetPixel(dc, x, y);
				RGBTRIPLE rgb;

				rgb.rgbtRed = GetRValue(color);
				rgb.rgbtGreen = GetGValue(color);
				rgb.rgbtBlue = GetBValue(color);

				if ((int)rgb.rgbtRed == 255 && (int)rgb.rgbtGreen == 177 && (int)rgb.rgbtBlue == 0) {
					frameAdvantage = 18;
					return;
				}
				else if ((int)rgb.rgbtRed == 255 && (int)rgb.rgbtGreen == 251 && (int)rgb.rgbtBlue == 0) {
					frameAdvantage = 15;
					return;
				}
				else if ((int)rgb.rgbtRed == 120 && (int)rgb.rgbtGreen == 251 && (int)rgb.rgbtBlue == 120) {
					frameAdvantage = 10;
					return;
				}
				else if ((int)rgb.rgbtRed == 170 && (int)rgb.rgbtGreen == 251 && (int)rgb.rgbtBlue == 255) {
					frameAdvantage = 12;
					return;
				}
				else if ((int)rgb.rgbtRed == 67 && (int)rgb.rgbtGreen == 98 && (int)rgb.rgbtBlue == 100) {
					frameAdvantage = 13;
					return;
				}
			}
		}
		std::cout << ".";
		Sleep(150);
	}
}