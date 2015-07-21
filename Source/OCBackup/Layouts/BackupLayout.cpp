#include "BackupLayout.h"
#include "ui_BackupLayout.h"


OCBackupLayout::OCBackupLayout(QWidget *parent, IBackupPresenter* presenter) :
    QWidget(parent),
    _presenter(presenter),
    ui(new Ui::OCBackupLayout)
{
    ui->setupUi(this);

    _qmlContext = ui->quickWidget->rootContext();
    //ui->quickWidget->engine()->addImageProvider(QString("thumbnail"), new ThumbnailProvider());

    //_qmlContext->setContextProperty("fileList", QVariant::fromValue(_fileList));

    ui->quickWidget->setSource(QUrl("./Widgets/ThumbnailView.qml"));
}

OCBackupLayout::~OCBackupLayout()
{
    delete ui;
}
