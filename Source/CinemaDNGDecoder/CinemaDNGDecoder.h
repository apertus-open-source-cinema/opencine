#include <string>
#include <vector>

#include "Defines.h"
#include "CinemaDNGFile.h"

class CinemaDNGDecoder
{
  CinemaDNGFile* DecodeData(CinemaDNGFile& file, std::vector<Byte> data);

public:
  CinemaDNGDecoder();

  CinemaDNGFile* LoadFile(std::string fileName);
};
