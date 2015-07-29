#include "OCLauncher.h"

#include <iostream>
#include <memory>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <OCui.h>

#include <Layouts/LauncherLayout.h>

class OCLauncher : public OCui::GUIApplication
{
     std::shared_ptr<QWidget> _layout;

public:
    OCLauncher(int argc, char** argv) : GUIApplication(argc, argv, "OCLauncher")
    {
//        QFile file;
//        file.setFileName("test.json");
//        file.open(QIODevice::ReadOnly | QIODevice::Text);
//        QString val = file.readAll();
//        file.close();
//        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
//        QJsonObject sett2 = d.object();
//        QJsonArray array = sett2["Applications"].toArray();

//        QStringList propertyNames;
//        QStringList propertyKeys;

//        for(const QJsonValue & value : array)
//        {
//            QJsonObject obj = value.toObject();
//            propertyNames.append(obj["Executable"].toString());
//            propertyKeys.append(obj["Image"].toString());
//        }

//        std::cout << array[0].toString().toStdString() << std::endl;
//        QJsonValue value = sett2.value(QString("Applications"));
//        std::cout << value.toString().toStdString() << std::endl;
//        QJsonValue value2 = sett2.value(QString("Image"));
//        std::cout << value2.toString().toStdString() << std::endl;
//        QJsonValue value3 = sett2.value(QString("Executable"));
//        std::cout << value3.toString().toStdString() << std::endl;
        int i = 0;

        _layout = std::make_shared<LauncherLayout>();//(nullptr, _presenter.get());
        SetLayout(*_layout.get());
    }
};

int main(int argc, char** argv)
{
    std::cout << "OCLauncher" << std::endl;

    std::shared_ptr<OCLauncher> backup = std::make_shared<OCLauncher>(argc, argv);
    backup->Run();

    return 0;
}
