#include "PunishStats.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

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

void PunishStats::readStatsFromFile(std::map<std::string, PunishStats>* punishStats)
{
	std::vector<std::string> strings;

	std::ifstream file("stats.csv");
	if (!file.good()) {
		return;
	}

	std::string firstLine;

	if (file.is_open()) {
		for (std::string line; getline(file, line);) {
			std::stringstream ss(line);
			std::string key = "";
			int i = 0;
			PunishStats stats;

			for (std::string field; getline(ss, field, ','); ) {
				switch (i) {
				case 0:
					key = field;
					break;
				case 1:
					stats.punishCount = std::stoi(field);
					break;
				case 2:
					stats.failureCount = std::stoi(field);
					break;
				}
				i++;
			}
			(*punishStats)[key] = stats;
		}
	}

}