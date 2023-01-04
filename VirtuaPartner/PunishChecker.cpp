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

		for (int x = 291; x <= 331; x++) {
			for (int y = 594; y <= 597; y++) {
				COLORREF color = GetPixel(dc, x, y);
				RGBTRIPLE rgb;

				rgb.rgbtRed = GetRValue(color);
				rgb.rgbtGreen = GetGValue(color);
				rgb.rgbtBlue = GetBValue(color);

				if ((int)rgb.rgbtRed == 255 && (int)rgb.rgbtGreen == 177 && (int)rgb.rgbtBlue == 0) {
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
			}
		}
		Sleep(150);
	}
}