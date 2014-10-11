#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Load an application style
    QString currentWD = QDir::currentPath();
    QFile mainStyleFile( "./Themes/DarkTheme.qss" );
    bool themeFound = mainStyleFile.open( QFile::ReadOnly );

    if(themeFound)
    {
        QString mainStyle( mainStyleFile.readAll() );
        w.setStyleSheet(mainStyle);
    }

    w.showMaximized();

    return a.exec();
}
