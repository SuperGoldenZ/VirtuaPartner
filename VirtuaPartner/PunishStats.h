#ifndef PUNISH_STATS
#define PUNISH_STATS

#include <string>
#include <map>

class PunishStats
{
public:
	int punishCount = 0;
	int failureCount = 0;
	std::string toString();
	static void readStatsFromFile(std::map<std::string, PunishStats> * punishStats);
};

#endif