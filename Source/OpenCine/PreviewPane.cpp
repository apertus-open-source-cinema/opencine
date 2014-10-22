#include "PreviewPane.h"
#include "ui_PreviewPane.h"

#include <QGLFormat>

PreviewPane::PreviewPane(QWidget *parent) :
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
    QGLFormat glFormat;
    glFormat.setVersion( 3, 3 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setDoubleBuffer(true);
    glFormat.setSampleBuffers(true);

    if ( !glFormat.sampleBuffers() )
    {
        int i = 0;
    }

    // Set the clear color to black
    glClearColor( 1.0f / 255.0f * 18.0f, 1.0f / 255.0f * 115.0f, 1.0f / 255.0f * 166.0f, 1.0f );
}
