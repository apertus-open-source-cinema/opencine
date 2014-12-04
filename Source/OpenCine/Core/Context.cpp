#include "Context.h"

#include <LibRawDataProvider.h>
#include <RawSpeedDataProvider.h>

OCContext::OCContext() :
_session(nullptr)
{
  DataProviderFactory* factory = new DataProviderFactory();

  factory->Register<LibRawDataProvider>(ClipType::DNG);
  //factory->Register<FFmpegDataProvider>(ClipType::MLV);
  //factory->Register<RawSpeedDataProvider>(ClipType::DNG);

  delete factory;

  _dataProvider = new LibRawDataProvider();

  std::map<ClipType, IDataProvider*> dataProviders;
  dataProviders.emplace(std::make_pair(ClipType::DNG, new LibRawDataProvider()));

  IDataProvider* provider = nullptr;

  std::map<ClipType, IDataProvider*>::iterator it = dataProviders.find(ClipType::DNG);
  if(it != dataProviders.end())
  {
    provider = it->second;
  }

  int i = 0;
}

void OCContext::LoadClip()
{
  emit SessionChanged();
}

//TODO: void CreateNewSession(std::string dataPath, IDataProvider& dataProvider)
