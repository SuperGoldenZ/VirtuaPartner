#ifndef PUNISH_STATS
#define PUNISH_STATS

#include <string>

class PunishStats
{
public:
	int punishCount = 0;
	int failureCount = 0;
	std::string toString();
};

#endif