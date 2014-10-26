#include "PreviewPane.h"
#include "ui_PreviewPane.h"

#include <QGLFormat>

PreviewPane::PreviewPane(IPlaybackPresenter* presenter, QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::PreviewPane)
{    
    ui->setupUi(this);

    //this->setAttribute(Qt::WA_DontCreateNativeAncestors);
}

PreviewPane::~PreviewPane()
{
    delete ui;
}

void PreviewPane::resizeGL(int w, int h)
{
    // Set the viewport to window dimensions
    glViewport( 0, 0, w, qMax( h, 1 ) );
}

void PreviewPane::paintGL()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void PreviewPane::initializeGL()
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    this->setFormat(format);

    // Set the clear color to black
    glClearColor( 1.0f / 255.0f * 18.0f, 1.0f / 255.0f * 115.0f, 1.0f / 255.0f * 166.0f, 1.0f );
}
