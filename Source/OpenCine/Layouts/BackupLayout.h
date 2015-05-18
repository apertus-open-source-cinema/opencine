#ifndef BACKUPLAYOUT_H
#define BACKUPLAYOUT_H

#include <QQmlContext>
#include <QQuickImageProvider>
#include <QWidget>

#include "BackupPresenter.h"

class ThumbnailProvider : public QQuickImageProvider
{
    QImage image;
    LibRawDataProvider dataProvider;
    StaticMemoryAllocator* dataStorage;

    // QQuickImageProvider interface
public:
    ThumbnailProvider()
            : QQuickImageProvider(QQuickImageProvider::Image)
        {
        }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

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
