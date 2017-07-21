// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef PATHINFO_H
#define PATHINFO_H

#include "OCCore_export.h"

class OCCORE_EXPORT PathInfo
{
public:
    std::string Path = "?";
    std::string RelativePath = "?";
	std::string DriveName = "?";
	std::string DrivePath = "?";

	unsigned long long UsedSpace = 0;
	unsigned long long TotalSpace = 0;

    //OBSOLETE: UI should handle it
    std::string SpaceUnit = "?";
};

#endif //PATHINFO_H
