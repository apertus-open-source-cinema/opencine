#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QtGlobal>

#include <QProcess>
#include <QSurfaceFormat>
#include <memory>

#include "DataStorage/StaticMemoryAllocator.h"
#include "DataProvider/LibRawDataProvider.h"
#include "DataProvider/FFmpegDataProvider.h"

#include "Core/Context.h"

//#include <OpenImageIO/imageio.h>
//OIIO_NAMESPACE_USING

#include "Tests.h"

using namespace OpenCineAPI;

void SetStyle(QApplication* app)
{
    QString currentWD = QDir::currentPath();
    QFile mainStyleFile( "./Themes/DarkTheme.qss" );
    bool themeFound = mainStyleFile.open( QFile::ReadOnly );

    if(themeFound)
    {
        QString mainStyle( mainStyleFile.readAll() );
        app->setStyleSheet(mainStyle);
    }
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type)
    {
    case QtDebugMsg:
        fprintf(stderr, "OC Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "OC Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "OC Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "OC Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

QProcess *proc;

void printOutput()
{
    //ui->e_Log->append("Got to printOutput()"); // TextEdit to see results

    QByteArray byteArray = proc->readAllStandardOutput();
    QStringList strLines = QString(byteArray).split("\n");

    foreach (QString line, strLines)
    {
        std::cout << line.toStdString() << std::endl;

        //ui->e_Log->append(line);
    }
}

void printError()
{
    //ui->e_Log->append("Got to printError()");

    QByteArray byteArray = proc->readAllStandardError();
    QStringList strLines = QString(byteArray).split("\n");

    foreach (QString line, strLines)
    {
        std::cout << line.toStdString() << std::endl;

        //ui->e_Log->append(line);
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if(app.arguments().count() > 1)
    {
        if(app.arguments().at(1) == "/test")
        {
            RunUnitTests();
        }

        return 0;
    }

    qInstallMessageHandler(myMessageOutput); //install : set the callback

    //ImageOutput *out = ImageOutput::create ("Test.img");

    //TestFFMPEG();
    //TestOpenCL();
    //TestCatch();
    //    QSurfaceFormat format;
    //    format.setVersion(3, 3);
    //    format.setProfile(QSurfaceFormat::CoreProfile);
    //    format.setDepthBufferSize(24);
    //    format.setStencilBufferSize(8);
    //    QSurfaceFormat::setDefaultFormat(format);

    //Idea: IDataProvider -> IDataStorage
    //      LibRawDataProvider -> StaticMemoryAllocator
    //      Example:
    //      IDataStorage* dataStorage = new StaticMemoryAllocator();
    //      IDataProvider* dataProvider = new LibRawDataProvider(dataStorage);
    //
    //      IDataStorage -> MediaExplorerPresenter
    //      IDataStorage -> ClipPreview

    //Step 1: Get some data -> "Model"
    //std::shared_ptr<IDataStorage> dataStorage = std::shared_ptr<StaticMemoryAllocator>(new StaticMemoryAllocator());
    //std::shared_ptr<IDataProvider> dataProvider = std::shared_ptr<LibRawDataProvider>(new LibRawDataProvider(dataStorage.get()));

    //Step 2: Pass data storage to "Presenter"
    //???

    //Step 3: Show data in "View"
    //???


    OCContext* context =  new OCContext();



    //proc = new QProcess(&app);

    //QObject::connect(proc, &QProcess::readyReadStandardOutput, printOutput);
    //QObject::connect(proc, &QProcess::readyReadStandardError, printError);

    std::cerr << "CERR: Console application running!" << std::endl;
    std::cout << "COUT: Console application running!" << std::endl;

    //proc->start();

    MainWindow* mainWindow = new MainWindow(context);
    mainWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    // Load an application style
    SetStyle(&app);

    mainWindow->showMaximized();

    return app.exec();
}
