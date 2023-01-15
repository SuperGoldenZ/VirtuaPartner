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

	const int TOP_ROW_Y = 512;
	const int THIRD_ROW_X = 537;
	const int COLUMN_6_P2_X = 958;

	if (checkPoint(1020 - (140 * 6), TOP_ROW_Y, r, g, b) ||
		checkPoint(210, TOP_ROW_Y, r, g, b) ||
		checkPoint(259 - 75, TOP_ROW_Y, r, g, b)
		) {
		return "Taka";
	}

	if (checkPoint(1020 - (140 * 5), TOP_ROW_Y, r, g, b)) {
		return "Akira";
	}

	if (checkPoint(THIRD_ROW_X, TOP_ROW_Y, r, g, b) || checkPoint(1010 - (140 * 4), TOP_ROW_Y, r, g, b)) {
		return "Pai";
	}

	if (checkPoint(1020 - (140 * 3), TOP_ROW_Y, r, g, b)) {
		return "Lau";
	}

	if (checkPoint(COLUMN_6_P2_X, TOP_ROW_Y, r, g, b) ||
		checkPoint(865, TOP_ROW_Y, r, g, b)
		) {
		return "Jeffry";
	}

	if (checkPoint(1028, TOP_ROW_Y, r, g, b) || checkPoint(1130, TOP_ROW_Y, r, g, b)) {
		return "Jean";
	}

	if (checkPoint(797, TOP_ROW_Y, r, g, b)) {
		return "Wolf";
	}

	// Bottom Row
	const int BOTTOM_ROW_Y = 667;

	if (checkPoint(1020 - (140 * 1), BOTTOM_ROW_Y, r, g, b)) {
		return "Goh";
	}

	if (checkPoint(1020 - (140 * 2), BOTTOM_ROW_Y, r, g, b)) {
		return "Brad";
	}

	if (checkPoint(1020 - (140 * 3), BOTTOM_ROW_Y, r, g, b)) {
		return "Vanessa";
	}

	if (checkPoint(THIRD_ROW_X, BOTTOM_ROW_Y, r, g, b)) {
		return "Lei-Fei";
	}

	if (checkPoint(1020 - (140 * 5), BOTTOM_ROW_Y, r, g, b)) {
		return "Aoi";
	}

	// Middle Row
	const int MIDDLE_ROW_Y = 564;

	if (checkPoint(1020, MIDDLE_ROW_Y, r, g, b) || checkPoint(1130, MIDDLE_ROW_Y, r, g, b)) {
		return "Blaze";
	}

	if (checkPoint(COLUMN_6_P2_X, MIDDLE_ROW_Y, r, g, b) ||
		checkPoint(865, MIDDLE_ROW_Y, r, g, b)
		) {
		return "Lion";
	}

	if (checkPoint(828, MIDDLE_ROW_Y, r, g, b)) {
		return "Shun";
	}

	if (checkPoint(280, MIDDLE_ROW_Y, r, g, b) ||
		checkPoint(270, MIDDLE_ROW_Y, r, g, b) ||
		checkPoint(209, MIDDLE_ROW_Y, r, g, b) ||
		checkPoint(190, MIDDLE_ROW_Y, r, g, b)
		) {
		return "Eileen";
	}


	if (checkPoint(682, MIDDLE_ROW_Y, r, g, b)) {
		return "Jacky";
	}

	if (checkPoint(THIRD_ROW_X, MIDDLE_ROW_Y, r, g, b)) {
		return "Sarah";
	}

	if (checkPoint(406, MIDDLE_ROW_Y, r, g, b)) {
		return "Kage";
	}

	return "Unknown";
}