#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    //QApplication::setGraphicsSystem();
    QApplication app(argc, argv);


    QQmlApplicationEngine engine;

           /* window.setAttribute(Qt::WA_OpaquePaintEvent);
    window.setAttribute(Qt::WA_NoSystemBackground);
    window.viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    window.viewport()->setAttribute(Qt::WA_NoSystemBackground);*/
    //engine.addImportPath("./3rdParty/Material/modules");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

