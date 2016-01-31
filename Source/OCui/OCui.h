#ifndef OCUI_H
#define OCUI_H

#include <memory>

#include <QObject>

#include "OCui_export.h"

class QApplication;
class MainWindow;
class QWidget;

namespace OCui
{
    class EXPORT_API GUIApplication : public QObject
    {
        std::shared_ptr<QApplication> _application;
        std::shared_ptr<MainWindow> _mainWindow;

        void SetStyle(QApplication &app);

    public:
        GUIApplication(int& argc, char** argv, std::string moduleName);

        void Show();
        void ShowMaximized();

        void SetWindowOptions(bool resizeable);

        void SetLayout(QWidget& widget);

        int Run();
    };
}

#endif //OCUI_H
