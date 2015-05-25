#include "Context.h"

#include <LibRawDataProvider.h>
#include <RawSpeedDataProvider.h>

OCContext::OCContext() :
_session(nullptr),
_dataProvider(nullptr)
{
  _factory = new DataProviderFactory();

  _factory->Register<LibRawDataProvider>(ClipType::DNG);
  //factory->Register<FFmpegDataProvider>(ClipType::MLV);
  //factory->Register<RawSpeedDataProvider>(ClipType::DNG);

  _dataProvider = _factory->Get(ClipType::DNG);

  //_factory->Get(ClipType::DNG); //new LibRawDataProvider();

  /*std::map<ClipType, IDataProvider*> dataProviders;
  dataProviders.emplace(std::make_pair(ClipType::DNG, new LibRawDataProvider(nullptr)));

  IDataProvider* provider = nullptr;

  std::map<ClipType, IDataProvider*>::iterator it = dataProviders.find(ClipType::DNG);
  if(it != dataProviders.end())
  {
    provider = it->second;
  }*/

  int i = 0;
}

OCContext::~OCContext()
{
  delete _factory;
}

void OCContext::LoadClip()
{
  emit SessionChanged(nullptr);
}

//TODO: void CreateNewSession(std::string dataPath, IDataProvider& dataProvider)
