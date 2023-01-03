#include <windows.h>
#include <tchar.h>
#include <string>

#include "PunishChecker.h"
#include "MciApi.h"

bool PunishChecker::checkPoint(HWND virtuaFighterWindow, int x, int y, int r, int g, int b)
{
	HDC dc = GetDC(virtuaFighterWindow);
	const COLORREF color = GetPixel(dc, x, y);
	RGBTRIPLE rgb;

	rgb.rgbtRed = GetRValue(color);
	rgb.rgbtGreen = GetGValue(color);
	rgb.rgbtBlue = GetBValue(color);

	return abs(r - (int)rgb.rgbtRed) <= 45 &&
		abs(g - (int)rgb.rgbtGreen) <= 45 &&
		abs(b - (int)rgb.rgbtBlue) <= 45;
}

bool PunishChecker::checkPoint(int x, int y, int r, int g, int b)
{
	const COLORREF color = GetPixel(dc, x, y);
	RGBTRIPLE rgb;

	rgb.rgbtRed = GetRValue(color);
	rgb.rgbtGreen = GetGValue(color);
	rgb.rgbtBlue = GetBValue(color);

	return ((int)rgb.rgbtRed == r && (int)rgb.rgbtGreen == g && (int)rgb.rgbtBlue == b);
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

std::string PunishChecker::getSelectedPlayer1(HWND vfWindow)
{
	if (!PunishChecker::checkPoint(vfWindow, 635, 74, 255, 232, 171)) {
		return "Unknown";
	}

	if (PunishChecker::checkPoint(vfWindow, 1120, 609, 255, 0, 0)) {
		return "Bla[z]e";
	}

	if (PunishChecker::checkPoint(vfWindow, 839, 609, 255, 0, 0)) {
		return "S[h]un";
	}

	if (PunishChecker::checkPoint(vfWindow, 280, 608, 255, 0, 0)) {
		return "[E]ileen";
	}

	return "Unknown";
}