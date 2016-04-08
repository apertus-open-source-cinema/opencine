#ifndef OCBACKUPLAYOUT_H
#define OCBACKUPLAYOUT_H

#include <memory>

#include <QWidget>
#include <QQmlContext>
#include <QStringListModel>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QtQml/QQmlComponent>
#include <QItemSelection>

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
	std::shared_ptr<QFileSystemModel> _folderTreeModel;

	QList<QObject*>* dataList;

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
	void SetCurrentFolder(QString folderPath);
	void SetDriveList(std::vector<DriveInfo> driveList);
	void SetItemList(std::vector<QString> fileList);
};

#endif // OCBACKUPLAYOUT_H
