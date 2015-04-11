#include <Poco/DirectoryIterator.h>

class IDataFilter
{
public:
  virtual bool ScanFolder(std::string folderPath) = 0;
};

class DNGFilter : public IDataFilter
{
  std::vector<std::string> fileNames;

public:
  bool ScanFolder(std::string folderPath)
  {
    std::string cwd(folderPath);
    Poco::DirectoryIterator it(cwd);
    Poco::DirectoryIterator end;
    while (it != end)
    {
      Poco::Path path(it->path());

      if (it->isFile() && path.getExtension() == "dng")
      {
        fileNames.push_back(path.getBaseName());
      }

      ++it;
    }

    // Sort the file names as they could have been added in wrong order by DirectoryIterator
    std::sort(fileNames.begin(), fileNames.end());

    return CheckSequenceNumbering();
  }

  bool CheckSequenceNumbering()
  {
    unsigned int prevNumber = std::stoi(fileNames.at(0));

    for(unsigned int index = 1; index < fileNames.size(); index++)
    {
      if(std::stoi(fileNames.at(index)) != prevNumber + 1)
      {
        return false;
      }

      prevNumber++;
    }

    return true;
  }
};
