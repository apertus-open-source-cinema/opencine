#ifndef PREVIEWPANE_H
#define PREVIEWPANE_H

#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QOpenGLPaintDevice>

#include "Presenter/PlaybackPresenter.h"
#include "Core/ImageData.h"

class IPresenter
{

};

class IPlaybackPresenter
{

};

namespace Ui {
class PreviewPane;
}

class PreviewPane : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit PreviewPane(PlaybackPresenter* presenter, QWidget *parent = 0);
    ~PreviewPane();

private:
    Ui::PreviewPane *ui;

    GLuint rectangleVBO;
    GLuint rectangleUV;

    //QOpenGLVertexArrayObject* vao;
    GLuint tex;
    GLuint tex2;

    GLuint shaderProgram;

    PlaybackPresenter* _presenter;

    void CreateRectangle();
    void CreateShaders();

    //QOpenGLPaintDevice* m_paintDevice;

private slots:
    //void UpdateFrame(OCFrame* image);
   void OnFrameChange(unsigned int frameNumber, OCFrame* frame);

protected:
    void resizeGL(int w, int h);
    void paintGL();
    void initializeGL();
};

#endif // PREVIEWPANE_H
