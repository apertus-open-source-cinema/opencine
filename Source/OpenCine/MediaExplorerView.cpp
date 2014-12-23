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

    qmlContext = ui->quickWidget->rootContext();

    //TODO: Item (double) click processing
    QObject* item = (QObject*)ui->quickWidget->rootObject();
    QObject::connect(item, SIGNAL(loadClip(int)), this, SLOT(LoadClip(int)));

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
     dataList.append(clipInfo);

     qmlContext->setContextProperty("listModel", QVariant::fromValue(dataList));

     //HACK: For testing purpose only, loads last added clip, should be moved when double-clicking on a clip in MediaExplorer works again
     _presenter->LoadClip(dataList.count());
}

void MediaExplorerView::LoadClip(int clipNumber)
{
    int i = 0;
}
