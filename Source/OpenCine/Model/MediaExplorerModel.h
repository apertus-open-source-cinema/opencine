#ifndef MEDIAEXPLORERMODEL_H
#define MEDIAEXPLORERMODEL_H

#include <string>
#include <vector>

class ClipData
{
  std::string _name;
  unsigned int _width;
  unsigned int _height;

};

class MediaExplorerModel
{
  std::vector<ClipData> _availableData;

public:

  //Currently single folder only, subfolders will be implemented later
  bool EnumerateAvailableData(std::string folderPath);
};

#endif //MEDIAEXPLORERMODEL_H
