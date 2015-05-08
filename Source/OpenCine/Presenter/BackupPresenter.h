#ifndef BACKUPPRESENTER_H
#define BACKUPPRESENTER_H

#include <QFileSystemModel>
#include <QObject>
#include <QStringListModel>
#include <QFileSystemWatcher>

#include "Context.h"

class BackupPresenter : public QObject
{
  Q_OBJECT

public:
  BackupPresenter(OCContext* context);
  ~BackupPresenter();

  QStringListModel* GetDriveListModel();
  QFileSystemModel* GetFolderTreeModel();

public slots:
  void CurrentDriveChanged(const QModelIndex& current, const QModelIndex& previous);

signals:
  void DriveSelectionChanged(QModelIndex diveRoot);

private slots:
  void UpdateMounts();
private:
  std::vector<std::string> GetMounts();

  OCContext* _context;
  OCSession* _session;

  QFileSystemWatcher* _fileWatcher;

  QStringListModel* _driveListModel;
  QFileSystemModel* _folderTreeModel;
};



#endif // BACKUPPRESENTER_H
