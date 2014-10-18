#include "ClipInformationItem.h"
#include "ui_ClipInformationItem.h"

ClipInformationItem::ClipInformationItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClipInformationItem)
{
    ui->setupUi(this);

    //QPixmap p("./clouds.jpg");
    // get label dimensions
    //int w = ui->thumbPreview->width();
    //int h = ui->thumbPreview->height();

    // set a scaled pixmap to a w x h window keeping its aspect ratio
    //ui->thumbPreview->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
}

ClipInformationItem::~ClipInformationItem()
{
    delete ui;
}

void ClipInformationItem::SetFilename(std::string fileName)
{
    ui->label->setText(fileName.c_str());
}
