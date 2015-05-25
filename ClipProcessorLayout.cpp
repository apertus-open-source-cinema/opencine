#include "ClipProcessorLayout.h"
#include "ui_ClipProcessorLayout.h"

ClipProcessorLayout::ClipProcessorLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClipProcessorLayout)
{
    ui->setupUi(this);
}

ClipProcessorLayout::~ClipProcessorLayout()
{
    delete ui;
}
