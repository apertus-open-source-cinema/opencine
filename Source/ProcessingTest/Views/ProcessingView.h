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

    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

    virtual void SetFrame(OCImage& image);
      
private slots:
    void on_pushButton_toggled(bool checked);

    void on_pushButton_3_toggled(bool checked);

    void on_pushButton_4_toggled(bool checked);

private:
    Ui::ProcessingView *ui;

    void LoadTexture();
};

#endif // PROCESSINGVIEW_H
