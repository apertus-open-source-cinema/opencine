#ifndef OCBACKUP_H
#define OCBACKUP_H

#include <OCui.h>
#include <QMessageBox>

#include "Presenters/BackupPresenter.h"
#include "Views/BackupView.h"

class OCBackup : public OCui::GUIApplication
{
    Q_OBJECT

    std::shared_ptr<IBackupView> _view;
    std::shared_ptr<IBackupPresenter> _presenter;

public:
    OCBackup(int& argc, char** argv) : OCui::GUIApplication(argc,argv, "OCBackup"),
        _view(std::make_shared<BackupView>()),
        _presenter(std::make_shared<BackupPresenter>(*_view))
    {
        SetupSignals();

       SetLayout(*_view);

       ShowMaximized();
    }

    void SetupSignals()
    {
        QObject::connect(_presenter.get(), SIGNAL(StartTransferSig(std::string)), this, SLOT(StartTransfer(std::string)));

    }

private slots:
    void StartTransfer(std::string drivePath)
    {
        int i = 0;

        //TEMPORARY: Gather all files and folders for drive backup, create list of folders

        //Get folders
        QDir::Filters filters = QDir::NoDotAndDotDot | QDir::AllDirs | QDir::NoSymLinks;
        QDirIterator dirIterator(QString::fromStdString(drivePath), filters, QDirIterator::Subdirectories);
        std::vector<QString> dirList;

        while(dirIterator.hasNext())
        {
            dirIterator.next();

            dirList.push_back(dirIterator.fileName());
        }

        filters = QDir::Files | QDir::NoSymLinks;
        QDirIterator fileIterator(QString::fromStdString(drivePath), filters, QDirIterator::Subdirectories);
        std::vector<QString> fileList;

        while(fileIterator.hasNext())
        {
            fileIterator.next();

            fileList.push_back(fileIterator.fileName());
        }

        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.exec();

    }
};

#endif //OCBACKUP_H
