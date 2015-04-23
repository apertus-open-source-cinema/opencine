#include "ClipProcessorLayout.h"
#include "PreviewPane.h"
#include "ui_ClipProcessorLayout.h"

ClipProcessorLayout::ClipProcessorLayout(QWidget *parent, const OCContext& context) :
    QWidget(parent),
    ui(new Ui::ClipProcessorLayout)
{
    ui->setupUi(this);

    PlaybackPresenter* playbackPresenter = new PlaybackPresenter(&const_cast<OCContext&>(context));
    ui->previewPane = new PreviewPane(playbackPresenter);
}

ClipProcessorLayout::~ClipProcessorLayout()
{
    delete ui;
}
