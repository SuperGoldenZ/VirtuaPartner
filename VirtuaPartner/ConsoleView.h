#ifndef VIRTUA_PARTNER_UI
#define VIRTUA_PARTNER_UI

#include <vector>
#include <string>

#include "PunishStats.h"
#include "Model.h"

class ConsoleView
{
private:
	const std::string WAIT_CHARACTERS = "|\\-/|\\-/";
	HANDLE hConsole;
	int getColor(bool selected);
	int waitIndex = 0;
public:
	ConsoleView();
	void clear_screen();
	void printCharacterName(std::string name, bool selected);
	void printCharacterName(std::string name, bool selected, int numEndline);
	void printCharacterName(std::string name, bool selected, int numEndline, int widthToPrint);
	void printMenu(Model model);
	void printStrings(const std::vector<std::string> strings);
	void showWaitingScreen();
};
#endif