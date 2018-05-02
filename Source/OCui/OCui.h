// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCui
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef OCUI_H
#define OCUI_H

#include <memory>

#include <QObject>

#include "OCui_export.h"
#include "Controls/ProgressDialog.h"
#include "Presenters/ProgressDialogPresenter.h"

class QApplication;
class MainWindow;
class QWidget;

namespace OCui
{
	class OCUI_EXPORT GUIApplication : public QObject
	{
		std::shared_ptr<QApplication> _application;
		std::shared_ptr<MainWindow> _mainWindow;

		void SetStyle() const;

	public:
		GUIApplication(int& argc, char** argv, QString moduleName);

		void Show() const;
		void ShowMaximized() const;

		void SetWindowOptions(bool resizeable) const;

		void SetLayout(QWidget& widget) const;

		int Run() const;
	};
}

#endif //OCUI_H
