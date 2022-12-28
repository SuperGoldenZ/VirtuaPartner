#include "PunishStats.h"

std::string PunishStats::toString()
{
	std::string result;
	int percent;

	if ((punishCount + failureCount) == 0) {
		percent = 0;
	}
	else {
		percent = ((float)punishCount / (float)(punishCount + failureCount)) * 100;
	}


	return std::to_string(punishCount) + "/" + std::to_string(failureCount + punishCount) + " " + std::to_string(percent) + "%";
}