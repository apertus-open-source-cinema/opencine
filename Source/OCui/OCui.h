#ifndef OCUI_H
#define OCUI_H

#include <memory>

#include <QObject>

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif

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

    virtual ~GUIApplication();

    void SetLayout(QWidget &widget);

    int Run();
};
}

#endif //OCUI_H
