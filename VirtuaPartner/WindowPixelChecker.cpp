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

std::string WindowPixelChecker::getSelectedPlayer1()
{
	//Check timer and costume type to make sure not to change character on stage select or in dojo
	if (!checkPoint(635, 74, 255, 232, 171) || !checkPoint(96, 473, 111, 98, 63)) {
		return "Unknown";
	}

	if (checkPoint(1020, 516 + 50, 255, 0, 0)) {
		return "Blaze";
	}

	if (checkPoint(1020 - (140 * 1), 516 + 50, 255, 0, 0)) {
		return "Lion";
	}

	if (checkPoint(1020 - (140 * 1), 667, 255, 0, 0)) {
		return "Goh";
	}

	if (checkPoint(1020 - (140 * 2), 667, 255, 0, 0)) {
		return "Brad";
	}

	if (checkPoint(1020 - (140 * 3), 667, 255, 0, 0)) {
		return "Vanessa";
	}

	if (checkPoint(1020 - (140 * 4), 667, 255, 0, 0)) {
		return "Lei-Fei";
	}

	if (checkPoint(1020 - (140 * 5), 667, 255, 0, 0)) {
		return "Aoi";
	}

	if (checkPoint(1020 - (140 * 3), 516 + 50, 255, 0, 0)) {
		return "Jacky";
	}

	if (checkPoint(1020 - (140 * 4), 516 + 50, 255, 0, 0)) {
		return "Sarah";
	}

	if (checkPoint(1020 - (140 * 5), 516 + 50, 255, 0, 0)) {
		return "Kage";
	}

	if (checkPoint(1020, 516, 255, 0, 0)) {
		return "Jean";
	}

	if (checkPoint(1020 - 140, 516, 255, 0, 0)) {
		return "Jeffrey";
	}

	if (checkPoint(1020 - (140 * 2), 516, 255, 0, 0)) {
		return "Wolf";
	}

	if (checkPoint(1020 - (140 * 3), 516, 255, 0, 0)) {
		return "Lau";
	}

	if (checkPoint(1020 - (140 * 4), 516, 255, 0, 0)) {
		return "Pai";
	}

	if (checkPoint(1020 - (140 * 5), 516, 255, 0, 0)) {
		return "Akira";
	}

	if (checkPoint(1020 - (140 * 6), 516, 255, 0, 0)) {
		return "Taka";
	}

	if (checkPoint(839, 609, 255, 0, 0)) {
		return "Shun";
	}

	if (checkPoint(280, 608, 255, 0, 0)) {
		return "Eileen";
	}

	return "Unknown";
}