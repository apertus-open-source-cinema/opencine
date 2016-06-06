#include <memory>
#include <thread>

#include <OCui.h>

#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>

#include "Views/ProcessingView.h"
#include "Presenters/ProcessingPresenter.h"

#include <Image/FramePool.h>

class ProcessingTest : public OCui::GUIApplication
{
	std::shared_ptr<IProcessingView> _view;
	std::shared_ptr<IProcessingPresenter> _presenter;

public:
	ProcessingTest(int& argc, char** argv) : OCui::GUIApplication(argc, argv, "ProcessingTest")
	{
		_view = std::make_shared<ProcessingView>();
		_presenter = std::make_shared<ProcessingPresenter>(*_view);

		SetLayout(*static_cast<QWidget*>(_view.get()));
		ShowMaximized();

		QtConcurrent::run(_presenter.get(), &IProcessingPresenter::Test);
	}
};

int main(int argc, char** argv)
{
	//int i = 0;
	//RawPoolAllocator* poolAllocator = new RawPoolAllocator(256 * 1024 * 1024);
	//void* ptr1 = poolAllocator->Allocate(12);

	//unsigned long long num = 0xDEADBEEFBEEFDEAD;
	//memcpy(ptr1, &num, 16);

	//void* ptr2 = poolAllocator->Allocate(8);
	//num = 0xDEADBEEFBEEFDEAD;
	//memcpy(ptr2, &num, 16);
	
	//OC::DataProvider::FramePool<size_t> framePool;
	//size_t* x = framePool.allocate();

//	using imType = unsigned char[16];;
//	MemoryPool<imType, 3840 * 2160 * 3 * 3> pool;
//	unsigned char* x = pool.allocate();
//	unsigned char* x2 = pool.newElement();
//
//	unsigned long long num = 0xDEADBEEFBEEFDEAD;
//	memcpy(x, &num, 16);
//
//	num = 0xFEEDBABAFEEDBABA;
//	memcpy(x2, &num, 16);
//
//	pool.deallocate(x);

	//std::shared_ptr<ProcessingTest> application = std::make_shared<ProcessingTest>(argc, argv);

	ProcessingTest* app = new ProcessingTest(argc, argv);
	app->Run();

	/*TransferTask* task = new TransferTask();
	delete task;

	ProgressDialog* progressDialog = new ProgressDialog();
	progressDialog->setModal(true);
	progressDialog->show();*/

	if (app != nullptr)
	{
		delete app;
	}

	return 0;
}