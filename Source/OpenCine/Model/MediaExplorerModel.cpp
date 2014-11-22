#include "MediaExplorerModel.h"

#include <QDir>

bool MediaExplorerModel::EnumerateAvailableData(std::string folderPath)
{
  QDir dir(QString::fromStdString(folderPath));

  QStringList filters;
  filters << "*.dng";
  dir.setNameFilters(filters);

  dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

  //Get metadata for the first file, no error checks available atm
  std::string fileName = dir.entryList().at(0).toStdString();
  OCImage* imageData = _dataProvider->GetMetadataFromFile(folderPath + "/" + fileName);

  if(imageData != nullptr)
  {
    emit NewDataAdded(imageData);
    return true;
  }

  return false;
}
