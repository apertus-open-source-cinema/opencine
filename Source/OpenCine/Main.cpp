#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>

#include <memory>

#include "DataStorage/StaticAllocator.h"

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
    //
    //      IDataStorage -> MediaExplorer
    //      IDataStorage -> ClipPreview

    QApplication a(argc, argv);
    std::unique_ptr<MainWindow> w = std::unique_ptr<MainWindow>(new MainWindow());

    // Load an application style
    SetStyle(w.get());

    w->showMaximized();

    return a.exec();
}
