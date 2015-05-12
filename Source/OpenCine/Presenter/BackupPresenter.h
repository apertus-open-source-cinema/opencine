#ifndef BACKUPPRESENTER_H
#define BACKUPPRESENTER_H

#include <QFileSystemModel>
#include <QObject>
#include <QStringListModel>
#include <QFileSystemWatcher>
#include <QItemSelection>

#include "Core/Context.h"
#include "Model/FileInfo.h"

class BackupPresenter : public QObject
{
  Q_OBJECT

public:
  BackupPresenter(OCContext* context);
  ~BackupPresenter();

  QStringListModel* GetDriveListModel();
  QFileSystemModel* GetFolderTreeModel();
  std::vector<FileInfo*> GetFileList();

public slots:
  void CurrentDriveChanged(const QModelIndex& current, const QModelIndex& previous);
  void CurrentFolderChanged(const QItemSelection& current, const QItemSelection& previous);

signals:
  void DriveSelectionChanged(QModelIndex diveRoot);
  void FolderChanged(std::vector<FileInfo*> fileList);

private slots:
  void UpdateMounts();
private:
  std::vector<std::string> GetMounts();

  std::vector<FileInfo*> _fileInfoList;

  OCContext* _context;
  OCSession* _session;

  QFileSystemWatcher* _fileWatcher;

  QStringListModel* _driveListModel;
  QFileSystemModel* _folderTreeModel;
};



#endif // BACKUPPRESENTER_H
