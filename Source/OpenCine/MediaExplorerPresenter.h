#ifndef MEDIAEXPLORERPRESENTER_H
#define MEDIAEXPLORERPRESENTER_H

#include <QObject>
#include <QMessageBox>
#include <IDataStorage.h>

using namespace OpenCineAPI;

class MediaExplorerPresenter : public QObject
{
    Q_OBJECT

public:
    MediaExplorerPresenter();
    ~MediaExplorerPresenter();

    //std::vector<std::string> GetData();

private:
    IDataStorage* _dataStorage;

signals:
    void NewDataAvailable(OCImage* image);
    void NewClipImported(std::string importedClip);

private slots:
    void OpenFolderSelection();
    void UpdateViews();
};

#endif //MEDIAEXPLORERPRESENTER_H
