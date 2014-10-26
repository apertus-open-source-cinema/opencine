#ifndef PREVIEWPANE_H
#define PREVIEWPANE_H

#include <QOpenGLWidget>

class IPresenter
{

};

class IPlaybackPresenter
{

};

namespace Ui {
class PreviewPane;
}

class PreviewPane : public QOpenGLWidget//, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit PreviewPane(IPlaybackPresenter* presenter, QWidget *parent = 0);
    ~PreviewPane();

private:
    Ui::PreviewPane *ui;

    // QGLWidget interface
protected:
    void resizeGL(int w, int h);
    void paintGL();
    void initializeGL();
};

#endif // PREVIEWPANE_H
