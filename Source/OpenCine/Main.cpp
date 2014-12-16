#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>

#include <QSurfaceFormat>
#include <memory>

#include "DataStorage/StaticMemoryAllocator.h"
#include "DataProvider/LibRawDataProvider.h"
#include "DataProvider/FFmpegDataProvider.h"

#include "Core/Context.h"

#include <OpenImageIO/imageio.h>
OIIO_NAMESPACE_USING

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

int main(int argc, char *argv[])
{
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

  QApplication app(argc, argv);
  MainWindow* mainWindow = new MainWindow(context);
  mainWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

  // Load an application style
  SetStyle(&app);

  mainWindow->showMaximized();

  return app.exec();
}
