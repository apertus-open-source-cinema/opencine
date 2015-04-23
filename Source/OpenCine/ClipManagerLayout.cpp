#include "ClipManagerLayout.h"
#include "ui_ClipManagerLayout.h"

ClipManagerLayout::ClipManagerLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClipManagerLayout)
{
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl("./Widgets/ThumbnailView.qml"));
}

ClipManagerLayout::~ClipManagerLayout()
{
    delete ui;
}
