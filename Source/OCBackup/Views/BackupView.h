#ifndef OCBACKUPLAYOUT_H
#define OCBACKUPLAYOUT_H

#include <memory>

#include <QWidget>
#include <QQmlContext>
#include <QStringListModel>
#include <QFileSystemModel>
#include <QStandardItemModel>

#include "../Interfaces/IBackupView.h"

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
    QFileSystemModel* _folderTreeModel;

    QList<QObject*>* dataList;

    void SetupDriveView();
    void SetupFolderView();

public:
    explicit BackupView(IBackupPresenter* presenter = nullptr);
    ~BackupView();

private slots:
    void TransferButtonClicked();
    void CurrentDriveChanged(int currentDrive);

public:
    void SetCurrentFolder(std::string folderPath);
    void SetDriveList(std::vector<DriveInfo> driveList);
};

#endif // OCBACKUPLAYOUT_H
