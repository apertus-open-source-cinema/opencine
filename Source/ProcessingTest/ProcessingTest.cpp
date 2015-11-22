#include <memory>
#include <thread>

#include <QDebug>

#include <OCui.h>
#include <QSurfaceFormat>

#include "ProcessingTest.h"
#include "Views/ProcessingView.h"
#include "Presenters/ProcessingPresenter.h"

int testData[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 , 19, 20};

void task1(std::string ID, int offset, int length)
{
    for(int i = offset; i < offset + length; i++)
    {
       qDebug() << ID.c_str() << ": " << testData[i];
    }
}

class ProcessingTest : public OCui::GUIApplication
{
    std::shared_ptr<IProcessingView> _view;
    std::shared_ptr<IProcessingPresenter> _presenter;

public:
    ProcessingTest(int& argc, char** argv) : OCui::GUIApplication(argc,argv, "ProcessingTest"),
        _view(std::make_shared<ProcessingView>()),
        _presenter(std::make_shared<ProcessingPresenter>(*_view))
    {
        //SetupSignals();

    std::thread t1(task1, "T1", 0 , 9);
    std::thread t2(task1, "T2", 9, 7);
    std::thread t3(task1, "T3", 16, 5);

    t1.join();
    t2.join();
    t3.join();

        qDebug() << "Test";

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
