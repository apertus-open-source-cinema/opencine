#ifndef OCBACKUPLAYOUT_H
#define OCBACKUPLAYOUT_H

#include <memory>

#include <QWidget>
#include <QQmlContext>

#include "../Interfaces/IBackupView.h"

class IBackupPresenter;

namespace Ui
{
class BackupView;
}

class BackupView : public IBackupView
{
    Q_OBJECT

public:
    explicit BackupView(/*QWidget *parent = 0,*/ IBackupPresenter* presenter = nullptr);
    ~BackupView();

//    void SetupDriveView();
//    void SetupFolderView();

private slots:
    void TransferButtonClicked();

private:
    Ui::BackupView *ui;

    QQmlContext* _qmlContext;
//    IBackupPresenter* _presenter;

//private slots:
//    void DriveListChanged(std::vector<std::string> driveList);
//    void SelectDrive(const QModelIndex& current, const QModelIndex& previous);

    // IBackupView interface
public:
    void SetDriveList(std::vector<std::string> driveList);
};

#endif // OCBACKUPLAYOUT_H
