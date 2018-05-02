#include "ClipProcessorLayout.h"
#include "PreviewPane.h"
#include "ui_ClipProcessorLayout.h"

ClipProcessorLayout::ClipProcessorLayout(QWidget *parent, const OCContext& context) :
    QWidget(parent),
    _context(&const_cast<OCContext&>(context)),
    ui(new Ui::ClipProcessorLayout)
{
    ui->setupUi(this);

    PlaybackPresenter* playbackPresenter = new PlaybackPresenter(_context);
    ui->previewPane = new PreviewPane(playbackPresenter);
}

ClipProcessorLayout::~ClipProcessorLayout()
{
    delete ui;
}
