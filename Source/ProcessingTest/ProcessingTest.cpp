#include <memory>
#include <thread>

#include <QDebug>

#include <OCui.h>
#include <QSurfaceFormat>

#include "ProcessingTest.h"
#include "Views/ProcessingView.h"
#include "Presenters/ProcessingPresenter.h"

class ProcessingTest : public OCui::GUIApplication
{
    std::shared_ptr<IProcessingView> _view;
    std::shared_ptr<IProcessingPresenter> _presenter;

public:
    ProcessingTest(int& argc, char** argv) : OCui::GUIApplication(argc,argv, "ProcessingTest"),
        _view(std::make_shared<ProcessingView>()),
        _presenter(std::make_shared<ProcessingPresenter>(*_view))
    {
        SetLayout(*_view);
        Show();
    }

};

int main(int argc, char** argv)
{
    std::shared_ptr<ProcessingTest> application = std::make_shared<ProcessingTest>(argc, argv);
    application->Run();

    return 0;
}
