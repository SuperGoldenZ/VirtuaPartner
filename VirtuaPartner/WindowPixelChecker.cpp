#include "WindowPixelChecker.h"

#include <windows.h>
#include <string>

WindowPixelChecker::WindowPixelChecker(HWND virtuaFighterWindow)
{
	_virtuaFighterWindow = virtuaFighterWindow;
	dc = GetDC(virtuaFighterWindow);
}

bool WindowPixelChecker::checkPoint(const int x, const int y, const int r, const int g, const int b)
{
	const COLORREF color = GetPixel(dc, x, y);
	RGBTRIPLE rgb;

	rgb.rgbtRed = GetRValue(color);
	rgb.rgbtGreen = GetGValue(color);
	rgb.rgbtBlue = GetBValue(color);

	return (
		abs(r - (int)rgb.rgbtRed) <= 25 &&
		abs(g - (int)rgb.rgbtGreen) <= 25 &&
		abs(b - (int)rgb.rgbtBlue) <= 25
		);
}

std::string WindowPixelChecker::getSelectedPlayer(int playerNum)
{
	int xOffset = 0;

	int r = 255;
	int g = 0;
	int b = 0;

	if (playerNum == 2) {
		r = 5;
		g = 199;
		b = 255;
	}

	//shun 2p
	//eileen 2p (accidentally taka)
	//
	//Check timer and costume type to make sure not to change character on stage select or in dojo
	if (!checkPoint(635, 74, 255, 232, 171) || !checkPoint(96, 473, 111, 98, 63)) {
		return "Unknown";
	}

	if (checkPoint(1020 + xOffset, 516 + 50, r, g, b)) {
		return "Blaze";
	}

	if (checkPoint(1020 - (140 * 1) + xOffset, 516 + 50, r, g, b)) {
		return "Lion";
	}

	if (checkPoint(1020 - (140 * 1) + xOffset, 667, r, g, b)) {
		return "Goh";
	}

	if (checkPoint(1020 - (140 * 2) + xOffset, 667, r, g, b)) {
		return "Brad";
	}

	if (checkPoint(1020 - (140 * 3) + xOffset, 667, r, g, b)) {
		return "Vanessa";
	}

	if (checkPoint(1020 - (140 * 4) + xOffset, 667, r, g, b)) {
		return "Lei-Fei";
	}

	if (checkPoint(1020 - (140 * 5) + xOffset, 667, r, g, b)) {
		return "Aoi";
	}

	if (checkPoint(1020 - (140 * 3) + xOffset, 516 + 50, r, g, b)) {
		return "Jacky";
	}

	if (checkPoint(1020 - (140 * 4) + xOffset, 516 + 50, r, g, b)) {
		return "Sarah";
	}

	if (checkPoint(1020 - (140 * 5) + xOffset, 516 + 50, r, g, b)) {
		return "Kage";
	}

	if (checkPoint(1020 + xOffset, 516, r, g, b) || checkPoint(1010, 519, r, g, b)) {
		return "Jean";
	}

	if (checkPoint(1020 - 140 + xOffset, 516, r, g, b)) {
		return "Jeffrey";
	}

	if (checkPoint(1020 - (140 * 2) + xOffset, 516, r, g, b)) {
		return "Wolf";
	}

	if (checkPoint(1020 - (140 * 3) + xOffset, 516, r, g, b)) {
		return "Lau";
	}

	if (checkPoint(1020 - (140 * 4) + xOffset, 516, r, g, b) || checkPoint(1010 - (140 * 4) + xOffset, 519, r, g, b)) {
		return "Pai";
	}

	if (checkPoint(1020 - (140 * 5) + xOffset, 516, r, g, b)) {
		return "Akira";
	}

	if (checkPoint(1020 - (140 * 6) + xOffset, 513, r, g, b) ||
		checkPoint(210 + xOffset, 515, r, g, b) ||
		checkPoint(259, 561, r, g, b) ||
		checkPoint(259 - 75, 561, r, g, b)
		) {
		return "Taka";
	}

	if (checkPoint(839 + xOffset, 609, r, g, b)) {
		return "Shun";
	}

	if (checkPoint(280 + xOffset, 608, r, g, b)) {
		return "Eileen";
	}

	return "Unknown";
}