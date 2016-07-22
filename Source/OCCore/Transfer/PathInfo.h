#ifndef PATHINFO_H
#define PATHINFO_H

#include "OCCore_export.h"

class OCCORE_EXPORT PathInfo
{
public:
	std::string DriveName = "?";
	std::string DrivePath = "?";
	unsigned long long UsedSpace = 0;
	unsigned long long TotalSpace = 0;
	std::string SpaceUnit = "?";
};

#endif //PATHINFO_H
