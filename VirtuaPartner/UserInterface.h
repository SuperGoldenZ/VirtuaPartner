#ifndef VIRTUA_PARTNER_UI
#define VIRTUA_PARTNER_UI

#include <vector>
#include <string>

#include "PunishStats.h"

class UserInterface
{
private:
	const std::string WAIT_CHARACTERS = "|\\-/|\\-/";
	HANDLE hConsole;
	int getColor(bool selected);
	int waitIndex = 0;
public:
	UserInterface();
	void clear_screen();
	void printCharacterName(std::string name, bool selected);
	void printCharacterName(std::string name, bool selected, int numEndline);
	void printCharacterName(std::string name, bool selected, int numEndline, int widthToPrint);
	void printMenu(std::vector<std::vector<std::string>> categories, std::string str, bool leftSide, std::string currentCategory, bool punishCheck, std::map<std::string, PunishStats> punishStats, std::map<std::string, bool> selectedStrings, std::string player1CharacterName);
	void printStrings(const std::vector<std::string> strings);
	void showWaitingScreen();
};
#endif