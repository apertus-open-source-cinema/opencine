#include <iostream>
#include <memory>

#include <OCui.h>

#include "OCBackup.h"
#include "Layouts/BackupLayout.h"

#include <xxhash.h>

/*void TestFunc()
{
    int i = 0;
}*/

class OCBackup : public OCui::GUIApplication
{
    std::shared_ptr<QWidget> _layout;

public:
    OCBackup(int argc, char** argv) : GUIApplication(argc, argv, "OCBackup")
    {
        _layout = std::make_shared<OCBackupLayout>();
        _layout->showFullScreen();
        SetLayout(*_layout.get());

        std::string test = "1234";
        unsigned __int32 hash = XXH32(test.c_str(), 4, 1);
        std::wstring test2 = L"1234";
        unsigned __int64 hash2 = XXH64(test2.c_str(), 4, 1);

        int i = 0;
    }
};

int main(int argc, char** argv)
{
    std::cout << "OCBackup" << std::endl;

    std::shared_ptr<OCBackup> backup = std::make_shared<OCBackup>(argc, argv);
    return backup->Run();
}
