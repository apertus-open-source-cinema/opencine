#include "MediaExplorerView.h"
#include "ui_MediaExplorerView.h"

#include <QMenu>

#include "Presenter/MediaExplorerPresenter.h"

DataObject::DataObject(QObject *parent)
    : QObject(parent)
{
}

DataObject::DataObject(const QString &name, const unsigned int& width, const unsigned int& height, QObject *parent)
    : QObject(parent), _name(name), _width(width), _height(height)
{
}

QString DataObject::name() const
{
    return _name;
}

void DataObject::setName(const QString &name)
{
    if (name != _name)
    {
        _name = name;
        emit nameChanged();
    }
}

unsigned int DataObject::width() const
{
    return _width;
}

void DataObject::setWidth(const unsigned int& width)
{
    if (width != _width)
    {
        _width = width;
        emit widthChanged();
    }
}


unsigned int DataObject::height() const
{
    return _height;
}

void DataObject::setHeight(const unsigned int& height)
{
    if (height != _height)
    {
        _height = height;
        emit heightChanged();
    }
}

/*QString DataObject::fps() const
{
    return _FPS;
}

void DataObject::setFPS(const QString &fps)
{
    if (fps != _FPS)
    {
        _FPS = fps;
        emit fpsChanged();
    }
}*/

MediaExplorerView::MediaExplorerView(MediaExplorerPresenter* presenter, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaExplorerView)
{
    ui->setupUi(this);

    _presenter = presenter;

    ui->quickWidget->setSource(QUrl("./Widgets/MediaExplorerList.qml"));

    qmlContext = ui->quickWidget->rootContext();

    //TODO: Item (double) click processing
    //QObject* item = (QObject*)ui->quickWidget->rootObject();
    //MyClass* myClass = new MyClass();
    //QObject::connect(item, SIGNAL(loadClip(int)), myClass, SLOT(cppSlot(int)));

    QMenu* importMenu = new QMenu();
    QAction* testAction = new QAction("Import from folder...", this);
    connect(testAction,SIGNAL(triggered()), _presenter, SLOT(ImportFolder()));
    importMenu->addAction(testAction);
    ui->pushButton_4->setMenu(importMenu);

    connect(_presenter,SIGNAL(NewDataFound(ClipInfo*)), this, SLOT(NewClipsFound(ClipInfo*)));
}

MediaExplorerView::~MediaExplorerView()
{
    delete ui;
}

void MediaExplorerView::NewClipsFound(ClipInfo* clipInfo)
{
     dataList.append(new DataObject(QString::fromStdString(clipInfo->GetName()), clipInfo->GetWidth(), clipInfo->GetHeight()));

     qmlContext->setContextProperty("listModel", QVariant::fromValue(dataList));

     //HACK: For testing purpose only, loads last added clip, should be moved when double-clicking on a clip in MediaExplorer works again
     _presenter->LoadClip(dataList.count());
}
