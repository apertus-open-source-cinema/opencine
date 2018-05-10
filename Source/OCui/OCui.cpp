// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCui
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include <memory>

#include <QApplication>
#include <QDir>
#include <QFontDatabase>
#include <QDebug>

#include "OCui.h"
#include "Layouts/MainWindow.h"

// For QML debugging
//#include <QQmlDebuggingEnabler>
//QQmlDebuggingEnabler enabler;

using namespace OCui;

GUIApplication::GUIApplication(int& argc, char** argv, QString moduleName) :
	_application(std::make_shared<QApplication>(argc, argv)),
	_mainWindow(std::make_shared<MainWindow>())
{
	_mainWindow->setWindowTitle(moduleName);

	QFontDatabase* fontDatabase = new QFontDatabase();
	if (fontDatabase->addApplicationFont("Fonts/Titillium-Regular.otf") == -1)
	{
		qCritical() << "couldn't add application font";
	}

	QFont f = fontDatabase->font("Titillium", "bold", 10);
	//f.setStyleStrategy(QFont::PreferAntialias);
	QApplication::setFont(f);
	delete fontDatabase;

	SetStyle();
}

void GUIApplication::SetLayout(QWidget& widget) const
{
	_mainWindow->SetLayout(widget);
}

int GUIApplication::Run() const
{
	return _application->exec();
}

//TODO: Maybe the parameter is not necessary, as there is only one application available, consider to remove later
void GUIApplication::SetStyle() const
{
	QString currentWD = QDir::currentPath();
	QFile mainStyleFile("./Themes/DarkTheme.qss");
	bool themeFound = mainStyleFile.open(QFile::ReadOnly);

	if (themeFound)
	{
		QString mainStyle(mainStyleFile.readAll());
		_application.get()->setStyleSheet(mainStyle);
	}
}

void GUIApplication::Show() const
{
	_mainWindow->show();
}

void GUIApplication::ShowMaximized() const
{
	_mainWindow->showMaximized();
}

void GUIApplication::SetWindowOptions(bool fixedSize) const
{
	if (fixedSize)
	{
		_mainWindow->setFixedSize(_mainWindow->width(), _mainWindow->height());
	}
}
