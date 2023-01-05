#include <windows.h>
#include <tchar.h>
#include <string>

#include "PunishChecker.h"
#include "MciApi.h"

PunishChecker::PunishChecker(HWND vfWindow) : WindowPixelChecker(vfWindow)
{
	frameAdvantage = -1;
	advantageClass = AdvantageClass::NONE;
	hitsLow = false;
	recoversLow = false;
}

void PunishChecker::playSuccessSound()
{
	mciSendString(_T("play success_02.wav"), NULL, 0, NULL);
}

void PunishChecker::playFailureSound()
{
	mciSendString(_T("play failed_01.wav"), NULL, 0, NULL);
}

void PunishChecker::getAdvantageAmount()
{
	advantageClass = AdvantageClass::NONE;

	for (int i = 0; i < 5; i++) {
		int x = 331;
		int y = 596;

		if (checkPoint(376, 602, 170, 251, 255)) {
			frameAdvantage = 13;
			advantageClass = AdvantageClass::PUNCH;
			return;
		}

		if (checkPoint(373, 593, 255, 251, 0) && !checkPoint(373, 581, 255, 251, 0)) {
			frameAdvantage = 14;
			advantageClass = AdvantageClass::ELBOW;
			return;

		}

		if (checkPoint(355, 602, 255, 251, 0)) {
			frameAdvantage = 16;
			advantageClass = AdvantageClass::ELBOW;
			return;
		}

		if (checkPoint(x, y, 255, 177, 0) && !checkPoint(355, 602, 255, 177, 0) && !checkPoint(355, 597, 255, 177, 0)) {
			frameAdvantage = 17;
			advantageClass = AdvantageClass::KNEE;
			return;
		}

		if (checkPoint(x, y, 255, 177, 0) && !checkPoint(355, 602, 255, 177, 0) && checkPoint(355, 597, 255, 177, 0)) {
			frameAdvantage = 19;
			advantageClass = AdvantageClass::KNEE;
			return;
		}

		/**
		* Check for others
		*/
		COLORREF color = GetPixel(dc, x, y);
		RGBTRIPLE rgb;

		rgb.rgbtRed = GetRValue(color);
		rgb.rgbtGreen = GetGValue(color);
		rgb.rgbtBlue = GetBValue(color);

		if ((int)rgb.rgbtRed == 255 && (int)rgb.rgbtGreen == 177 && (int)rgb.rgbtBlue == 0 && checkPoint(355, 602, 255, 177, 0)) {
			frameAdvantage = 18;
			advantageClass = AdvantageClass::KNEE;
			return;
		}
		else if ((int)rgb.rgbtRed == 255 && (int)rgb.rgbtGreen == 251 && (int)rgb.rgbtBlue == 0) {
			frameAdvantage = 15;
			advantageClass = AdvantageClass::ELBOW;
			return;
		}
		else if ((int)rgb.rgbtRed == 120 && (int)rgb.rgbtGreen == 251 && (int)rgb.rgbtBlue == 120) {
			frameAdvantage = 10;
			advantageClass = AdvantageClass::THROW;
			return;
		}
		else if ((int)rgb.rgbtRed == 170 && (int)rgb.rgbtGreen == 251 && (int)rgb.rgbtBlue == 255) {
			frameAdvantage = 12;
			advantageClass = AdvantageClass::PUNCH;
			return;
		}
		else if ((int)rgb.rgbtRed == 67 && (int)rgb.rgbtGreen == 98 && (int)rgb.rgbtBlue == 100) {
			frameAdvantage = 13;
			advantageClass = AdvantageClass::PUNCH;
			return;
		}


		Sleep(150);
	}
}