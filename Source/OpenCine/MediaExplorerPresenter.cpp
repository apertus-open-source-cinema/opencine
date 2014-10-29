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

std::vector<std::string> MediaExplorerPresenter::GetData()
{
    std::vector<std::string> data;

    data.push_back("Test 1");
    data.push_back("Test 2");
    data.push_back("Test 3");

    return data;
}
