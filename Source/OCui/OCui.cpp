#include <memory>

#include <QApplication>
#include <QDir>
#include <QFontDatabase>
#include <QDebug>

#include "OCui.h"
#include "Layouts/MainWindow.h"

using namespace OCui;

GUIApplication::GUIApplication(int& argc, char** argv, std::string moduleName) :
    _application(std::make_shared<QApplication>(argc, argv)),
    _mainWindow(std::make_shared<MainWindow>())
{
    _mainWindow->setWindowTitle(moduleName.c_str());
    _mainWindow->showMaximized();

    QFontDatabase* fontDatabase = new QFontDatabase();
    if(fontDatabase->addApplicationFont("Fonts/Titillium-Regular.otf") == -1)
    {
        qCritical() << "couldn't add application font";
    }

    QFont f = fontDatabase->font("Titillium", "bold", 10);
    f.setStyleStrategy(QFont::PreferAntialias);
    QApplication::setFont(f);

    SetStyle(*_application.get());
}

GUIApplication::~GUIApplication()
{

}

void GUIApplication::SetLayout(QWidget& widget)
{
    _mainWindow->SetLayout(widget);
}

int GUIApplication::Run()
{
    return _application->exec();
}

void GUIApplication::SetStyle(QApplication& app)
{
    QString currentWD = QDir::currentPath();
    QFile mainStyleFile( "./Themes/DarkTheme.qss" );
    bool themeFound = mainStyleFile.open( QFile::ReadOnly );

    if(themeFound)
    {
        QString mainStyle( mainStyleFile.readAll() );
        app.setStyleSheet(mainStyle);
    }
}

