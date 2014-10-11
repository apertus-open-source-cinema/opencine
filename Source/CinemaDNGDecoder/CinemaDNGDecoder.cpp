#include "CinemaDNGDecoder.h"

#include <fstream>

using namespace std;

CinemaDNGDecoder::CinemaDNGDecoder()
{
}

CinemaDNGFile* CinemaDNGDecoder::LoadFile(string fileName)
{
  CinemaDNGFile* dngFile = new CinemaDNGFile();

  ifstream dataFile(fileName, ios::binary);

  //Get file size:
  dataFile.seekg(0, std::ios::end);
  unsigned int fileSize = dataFile.tellg();
  dataFile.seekg(0, std::ios::beg);

  //Read the data
  std::vector<Byte> data(fileSize);
  dataFile.read((char*) &data[0], fileSize);

  DecodeData(*dngFile, data);

  return dngFile;
}

CinemaDNGFile* CinemaDNGDecoder::DecodeData(CinemaDNGFile& file, vector<Byte> data)
{
  file.SetWidth(234);
  file.SetHeight(567);
}
