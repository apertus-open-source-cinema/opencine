#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>

#include <memory>

#include "DataStorage/StaticMemoryAllocator.h"
#include "DataProvider/LibRawDataProvider.h"

using namespace OpenCineAPI;

void SetStyle(MainWindow* w)
{
    QString currentWD = QDir::currentPath();
    QFile mainStyleFile( "./Themes/DarkTheme.qss" );
    bool themeFound = mainStyleFile.open( QFile::ReadOnly );

    if(themeFound)
    {
        QString mainStyle( mainStyleFile.readAll() );
        w->setStyleSheet(mainStyle);
    }
}

int main(int argc, char *argv[])
{
    //Idea: IDataProvider -> IDataStorage
    //      LibRawDataProvider -> StaticMemoryAllocator
    //      Example:
    //      IDataStorage* dataStorage = new StaticMemoryAllocator();
    //      IDataProvider* dataProvider = new LibRawDataProvider(dataStorage);
    //
    //      IDataStorage -> MediaExplorerPresenter
    //      IDataStorage -> ClipPreview

    //Step 1: Get some data -> "Model"
    std::shared_ptr<IDataStorage> dataStorage = std::shared_ptr<StaticMemoryAllocator>(new StaticMemoryAllocator());
    std::shared_ptr<IDataProvider> dataProvider = std::shared_ptr<LibRawDataProvider>(new LibRawDataProvider(dataStorage.get()));

    //Step 2: Pass data storage to "Presenter"
    //???

    //Step 3: Show data in "View"
    //???

    QApplication a(argc, argv);
    std::unique_ptr<MainWindow> w = std::unique_ptr<MainWindow>(new MainWindow());

    // Load an application style
    SetStyle(w.get());

    w->showMaximized();

    return a.exec();
}
