#include <windows.h>
#include <chrono>
#include <thread>
#include <tchar.h>
#include <stdio.h>
#include <iostream>

#include "PunishCheckerBlaze.h"

PunishCheckerBlaze::PunishCheckerBlaze(HWND virtuaFighterWindow, bool recoversLow) {
	_virtuaFighterWindow = virtuaFighterWindow;
	dc = GetDC(virtuaFighterWindow);
	frameAdvantage = -1;
	this->recoversLow = recoversLow;
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

void PunishCheckerBlaze::giveFeedback() {
	frameAdvantage = -1;

	std::thread getAdvantageThread([this] {this->getAdvantageAmount(); });
	getAdvantageThread.join();

	if (frameAdvantage == -1) {
		return;
	}

	std::thread judgePunishmentThread([this] {this->judgePunishment(); });
	judgePunishmentThread.join();
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

void PunishCheckerBlaze::judgePunishment()
{
	bool maxPunishment = false;
	bool guaranteedDamage = true;
	bool cpuKnockdown = false;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	switch (frameAdvantage) {
	case 12:
		if (didPkCounter()) {
			maxPunishment = true;
		}
		break;
	case 15:
		if (!recoversLow) {
			//Add delay since cuffis takes longer to execute
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
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

	if (guaranteedDamage && maxPunishment) {
		//clear_screen();
		//setDefaultConsoleText(36);
		playSuccessSound();
		std::cout << "MAX PUNISH!";

		//Wait for the CPU to get back up if they were knocked down
		if (cpuKnockdown) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		}
	}
	else if (guaranteedDamage) {
		//clear_screen();
		//setDefaultConsoleText(36);
		playFailureSound();
		std::cout << "Missed Punish";
	}
}

void PunishCheckerBlaze::playSuccessSound()
{
	mciSendString(_T("play success_02.wav"), NULL, 0, NULL);
	system("color a1");
}

void PunishCheckerBlaze::playFailureSound()
{
	mciSendString(_T("play failed_01.wav"), NULL, 0, NULL);
	system("color c0");
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
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}