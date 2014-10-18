#include "CinemaDNGDecoder.h"

#include <fstream>

CinemaDNGDecoder::CinemaDNGDecoder()
{
}

CinemaDNGFile* CinemaDNGDecoder::LoadFile(std::string fileName)
{
  CinemaDNGFile* dngFile = new CinemaDNGFile();

  std::ifstream dataFile(fileName, std::ios::binary);

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

CinemaDNGFile* CinemaDNGDecoder::DecodeData(CinemaDNGFile& file, std::vector<Byte> data)
{
  file.SetWidth(234);
  file.SetHeight(567);

  return nullptr;
}
