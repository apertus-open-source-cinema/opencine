#include "MediaExplorer.h"
#include "ui_MediaExplorer.h"

#include <QQmlContext>

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

MediaExplorer::MediaExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaExplorer)
{
    ui->setupUi(this);

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
}

MediaExplorer::~MediaExplorer()
{
    delete ui;
}
