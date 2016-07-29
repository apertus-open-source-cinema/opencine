#ifndef OCBACKUPLAYOUT_H
#define OCBACKUPLAYOUT_H

#include <memory>

#include <QQmlContext>
#include <QStringListModel>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QtQml/QQmlComponent>
#include <QItemSelection>

//#include "Data/DestinationsListItem.h"
#include "Interfaces/IBackupView.h"

class IBackupPresenter;

namespace Ui
{
    class BackupView;
}

class BackupView : public IBackupView
{
    Q_OBJECT

    Ui::BackupView *ui;
    QQmlContext* _qmlContext;

    QStringListModel* _driveListModel;
    std::shared_ptr<QFileSystemModel> _folderTreeModel;

    QList<QObject*> dataList;
    QList<QObject*>* _fileList;
    QList<QObject*> _destinationList;

    void SetupDriveView();
    void SetupFolderView();
    void SetupThumbnailView();
    void SetupDestinationsView();

public:
    explicit BackupView(IBackupPresenter* presenter = nullptr);
    ~BackupView();

private slots:
    void TransferButtonClicked();
    void CurrentDriveChanged(int currentDrive);
    void CurrentFolderChanged(const QItemSelection& selected, const QItemSelection& deselected);

public:
    void SetCurrentFolder(QString folderPath) override;
    void SetDriveList(std::vector<PathInfo> driveList) override;
    void SetItemList(std::vector<FileInfo> fileList) override;
    void SetDestinationList(std::vector<PathInfo> destinationList) override;
};

#endif // OCBACKUPLAYOUT_H
