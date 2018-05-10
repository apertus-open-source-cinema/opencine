#include "MediaExplorerView.h"
#include "ui_MediaExplorerView.h"

#include <QMenu>

#include "Presenter/MediaExplorerPresenter.h"

MediaExplorerView::MediaExplorerView(MediaExplorerPresenter* presenter, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaExplorerView)
{
    ui->setupUi(this);

    _presenter = presenter;

    ui->quickWidget->setSource(QUrl("./Widgets/MediaExplorerList.qml"));

    _qmlContext = ui->quickWidget->rootContext();

    //TODO: Item (double) click processing
    QObject* item = (QObject*)ui->quickWidget->rootObject();
    QObject::connect(item, SIGNAL(loadClip(int)), SLOT(LoadClip(int)));

    QMenu* importMenu = new QMenu();
    QAction* testAction = new QAction("Import from folder...", this);
    connect(testAction,SIGNAL(triggered()), _presenter, SLOT(ImportFolder()));
    importMenu->addAction(testAction);
    ui->pushButton_4->setMenu(importMenu);

    connect(_presenter,SIGNAL(NewDataFound(ClipItem*)), SLOT(NewClipsFound(ClipItem*)));
}

MediaExplorerView::~MediaExplorerView()
{
    delete ui;
}

void MediaExplorerView::NewClipsFound(ClipItem* clipInfo)
{
     _dataList.append(clipInfo);

     _qmlContext->setContextProperty("listModel", QVariant::fromValue(_dataList));

     //HACK: For testing purpose only, loads last added clip, should be moved when double-clicking on a clip in MediaExplorer works again
     _presenter->LoadClip(_dataList.count() - 1);
}

void MediaExplorerView::LoadClip(int clipNumber)
{
    int i = 0;
}
