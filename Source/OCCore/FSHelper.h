#ifndef FSHELPER_H
#define FSHELPER_H

#include <string>
#include <vector>

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif

//std::vector<std::string> EXPORT_API GetMounts();

class EXPORT_API IDriveManager
{
public:
    virtual ~IDriveManager() {}
    virtual std::vector<std::string> GetRemovableDrives() = 0;
};

class EXPORT_API DriveManager : public IDriveManager
{
    void EnumerateRemovableDrives(std::vector<std::string> availableDrives, std::vector<std::string>& removableDrives);

public:
    std::vector<std::string> GetRemovableDrives();
};

#endif //FSHELPER_H
