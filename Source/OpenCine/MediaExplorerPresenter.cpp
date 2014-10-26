#include "MediaExplorerPresenter.h"

#include <QFileDialog>

MediaExplorerPresenter::MediaExplorerPresenter()
{
}

MediaExplorerPresenter::~MediaExplorerPresenter()
{
}

void MediaExplorerPresenter::TestMessage()
{
    QString dir = QFileDialog::getExistingDirectory(0, tr("_Choose directory to import from ..."), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}
