#ifndef MEDIAEXPLORERPRESENTER_H
#define MEDIAEXPLORERPRESENTER_H

#include <QObject>
#include <QMessageBox>

//#include <IDataStorage.h>

#include "../Model/MediaExplorerModel.h"

//using namespace OpenCineAPI;

class IMediaExplorerPresenter
{
  virtual void ImportFolder() = 0;
  //virtual void UpdateViews() = 0;
};

class MediaExplorerPresenter : public QObject, public IMediaExplorerPresenter
{
    Q_OBJECT

public:
    MediaExplorerPresenter();
    ~MediaExplorerPresenter();

    //std::vector<std::string> GetData();

private:
    MediaExplorerModel* _model;

signals:
    //void NewDataAvailable(OCImage* image);
    void NewDataFound(ClipData*);

private slots:
    void ImportFolder();

    //void OpenFolderSelection();
    //void UpdateViews();
};

#endif //MEDIAEXPLORERPRESENTER_H
