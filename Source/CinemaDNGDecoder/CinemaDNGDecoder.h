#include <string>
#include <vector>

#include "Defines.h"
#include "CinemaDNGFile.h"

using namespace std;

class CinemaDNGDecoder
{
  CinemaDNGFile* DecodeData(CinemaDNGFile& file, vector<Byte> data);

public:
  CinemaDNGDecoder();

  CinemaDNGFile* LoadFile(string fileName);
};
