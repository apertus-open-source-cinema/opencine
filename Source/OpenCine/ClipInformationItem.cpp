#include "ClipInformationItem.h"
#include "ui_ClipInformationItem.h"

ClipInformationItem::ClipInformationItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClipInformationItem)
{
    ui->setupUi(this);
}

ClipInformationItem::~ClipInformationItem()
{
    delete ui;
}

void ClipInformationItem::SetFilename(std::string fileName)
{
    ui->label->setText(fileName.c_str());
}
