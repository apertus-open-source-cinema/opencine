#include <iostream>
#include <memory>

#include "OCBackup.h"

OCBackup::OCBackup(int &argc, char **argv) : OCui::GUIApplication(argc, argv, "OCBackup"),
_view(std::make_shared<BackupView>()),
_presenter(std::make_shared<BackupPresenter>(*_view))
{
	SetLayout(*_view);

	ShowMaximized();
}

int main(int argc, char** argv)
{
	std::shared_ptr<OCBackup> backup = std::make_shared<OCBackup>(argc, argv);
	backup->Run();

	return 0;
}