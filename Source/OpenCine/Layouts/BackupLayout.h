#ifndef BACKUPLAYOUT_H
#define BACKUPLAYOUT_H

#include <QQmlContext>
#include <QWidget>

#include "BackupPresenter.h"

namespace Ui {
class BackupLayout;
}

class BackupLayout : public QWidget
{
    Q_OBJECT

public:
    explicit BackupLayout(QWidget *parent = 0, const BackupPresenter& backupPresenter = BackupPresenter(nullptr));
    ~BackupLayout();

private slots:
    void DriveListChanged();
    void DriveSelectionChanged(QModelIndex driveRoot);
    void FolderSelectionChanged(std::vector<FileInfo*>);

private:
    Ui::BackupLayout *ui;

    BackupPresenter* _presenter;
    QQmlContext* _qmlContext;

    QList<QObject*> _fileList;
};

#endif // BACKUPLAYOUT_H
