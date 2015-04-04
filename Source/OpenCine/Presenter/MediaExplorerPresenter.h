#ifndef MEDIAEXPLORERPRESENTER_H
#define MEDIAEXPLORERPRESENTER_H

#include <QObject>
#include <QMessageBox>

#include "Core/Context.h"
#include "../Model/MediaExplorerModel.h"

class IMediaExplorerPresenter
{
  virtual void ImportFolder() = 0;
};

class MediaExplorerPresenter : public QObject, public IMediaExplorerPresenter
{
    Q_OBJECT

public:
    MediaExplorerPresenter(OCContext* context);
    ~MediaExplorerPresenter();

    void LoadClip(unsigned int clipNumber);

private:
    MediaExplorerModel* _model;

    OCContext* _context;

signals:
    void NewDataFound(ClipItem*);

private slots:
    void ImportFolder();
};

#endif //MEDIAEXPLORERPRESENTER_H
