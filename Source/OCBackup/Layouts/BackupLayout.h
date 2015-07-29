#ifndef OCBACKUPLAYOUT_H
#define OCBACKUPLAYOUT_H

#include <memory>

#include <QWidget>
#include <QQmlContext>

class IBackupPresenter;

namespace Ui
{
class OCBackupLayout;
}

class OCBackupLayout : public QWidget
{
    Q_OBJECT

public:
    explicit OCBackupLayout(QWidget *parent = 0, IBackupPresenter* presenter = nullptr);
    ~OCBackupLayout();

    void SetupDriveView();
    void SetupFolderView();

private:
    Ui::OCBackupLayout *ui;

    QQmlContext* _qmlContext;
    IBackupPresenter* _presenter;

private slots:
    void DriveListChanged(std::vector<std::string> driveList);
    void SelectDrive(const QModelIndex& current, const QModelIndex& previous);
};

#endif // OCBACKUPLAYOUT_H
