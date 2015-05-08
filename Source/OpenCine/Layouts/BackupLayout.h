#ifndef BACKUPLAYOUT_H
#define BACKUPLAYOUT_H

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
    void DriveSelectionChanged(QModelIndex driveRoot);
    void DriveListChanged();

private:
    Ui::BackupLayout *ui;

    BackupPresenter* _presenter;
};

#endif // BACKUPLAYOUT_H
