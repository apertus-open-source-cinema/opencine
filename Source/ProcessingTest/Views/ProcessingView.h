#ifndef PROCESSINGVIEW_H
#define PROCESSINGVIEW_H

#include <QWidget>

#include "Interfaces/IProcessingView.h"

namespace Ui {
class ProcessingView;
}

class ProcessingView : public IProcessingView
{
    Q_OBJECT

public:
    explicit ProcessingView(QWidget *parent = 0);
    ~ProcessingView();

    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

private:
    Ui::ProcessingView *ui;

    void LoadTexture();
};

#endif // PROCESSINGVIEW_H
