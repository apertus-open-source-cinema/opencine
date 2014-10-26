#include "MediaExplorerView.h"
#include "ui_MediaExplorerView.h"

#include <QQmlContext>

#include "MediaExplorerPresenter.h"

DataObject::DataObject(QObject *parent)
    : QObject(parent)
{
}

DataObject::DataObject(const QString &name, const QString &fps, QObject *parent)
    : QObject(parent), _name(name), _FPS(fps)
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

QString DataObject::fps() const
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
}

MediaExplorerView::MediaExplorerView(MediaExplorerPresenter* presenter, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaExplorerView)
{
    ui->setupUi(this);

    _presenter = presenter;

    ui->quickWidget->setSource(QUrl("./Widgets/MediaExplorerList.qml"));

    /*QStringList dataList;
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");*/

    QList<QObject*> dataList;
    dataList.append(new DataObject("Clip 1", "24"));
    dataList.append(new DataObject("Clip 2", "48"));
    dataList.append(new DataObject("Clip 3", "30"));
    dataList.append(new DataObject("Clip 4", "29"));

    QQmlContext *ctxt = ui->quickWidget->rootContext();
    ctxt->setContextProperty("listModel", QVariant::fromValue(dataList));

    QObject* item = (QObject*)ui->quickWidget->rootObject();
    MyClass* myClass = new MyClass();
    QObject::connect(item, SIGNAL(loadClip(int)), myClass, SLOT(cppSlot(int)));

    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), _presenter, SLOT(TestMessage()));
}

MediaExplorerView::~MediaExplorerView()
{
    delete ui;
}
