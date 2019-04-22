// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "PreviewPane.h"

#include <QWheelEvent>

using namespace OC::Image;

// unsigned char pixels[12] = {
//    255,   0, 0,     0, 255,   0,
//    0, 255, 0,     0,   0, 255
//};

// float xOffset = 0.5f / 4096.0f;
// float yOffset = 0.5f / 3072.0f;

// Create a colored triangle
static const float vertices[] = {-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0, 0.0, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0, 1.0,
                                 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0, 0.0, 1.0f,  -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0, 1.0};

PreviewPane::PreviewPane(QWidget *parent) : QOpenGLWidget(parent), _initialized(false)
{
    setMouseTracking(true);

    _renderingEnabled = false;

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
}

PreviewPane::~PreviewPane()
{
    delete program;
}

void PreviewPane::initializeGL()
{
    initializeOpenGLFunctions();

    printVersionInformation();

    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    SetupShaders();
    SetupVertexBuffer();
    SetupObject();
    // SetupTexture();

    object.release();
    vertex.release();
    program->release();

    _initialized = true;

    glGenTextures(1, &textureRed);
    glGenTextures(1, &textureGreen);
    glGenTextures(1, &textureBlue);
}

void PreviewPane::resizeGL(int w, int h)
{
    viewWidth = static_cast<float>(w) / static_cast<float>(h);
}

void PreviewPane::paintGL()
{
    if(!_renderingEnabled)
    {
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    program->bind();
    {
        QMatrix4x4 projection;
        projection.ortho(-viewWidth / 2.0f, viewWidth / 2.0f, -viewHeight / 2.0f, viewHeight / 2.0f, 0.01f, 1000.0f);
        QMatrix4x4 view;
        view.lookAt(QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0));
        QMatrix4x4 model;
        model.setToIdentity();
        model.scale(static_cast<float>(imageWidth) / static_cast<float>(imageHeight) * wheelValue, 1.0f * wheelValue, 1.0f);
        model.translate(panX, panY);

        mvp = projection * view * model;

        program->setUniformValue("MVP", mvp);

        object.bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureRed);
        program->setUniformValue("texture1", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureGreen);
        program->setUniformValue("texture2", 1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textureBlue);
        program->setUniformValue("texture3", 2);

        program->setUniformValue("redEnabled", static_cast<float>(redChannel));
        program->setUniformValue("greenEnabled", static_cast<float>(greenChannel));
        program->setUniformValue("blueEnabled", static_cast<float>(blueChannel));

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindTexture(GL_TEXTURE_2D, 0);
        object.release();
    }
    program->release();

    this->update();
}

void PreviewPane::printVersionInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));

    // Get Profile Information
#define CASE(c)                                                                                                                  \
    case QSurfaceFormat::c:                                                                                                      \
        glProfile = #c;                                                                                                          \
        break
    switch(format().profile())
    {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
#undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

void PreviewPane::SetupShaders()
{
    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/simple_shader.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/simple_shader.frag");
    program->link();
    program->bind();
}

void PreviewPane::SetupVertexBuffer()
{
    vertex.create();
    vertex.bind();
    vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertex.allocate(vertices, sizeof(vertices));
}

void PreviewPane::SetupObject()
{
    // Create Vertex Array Object
    object.create();
    object.bind();

    program->enableAttributeArray(0);
    program->enableAttributeArray(1);
    program->enableAttributeArray(2);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 8 * sizeof(float));
    program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 3, 8 * sizeof(float));
    program->setAttributeBuffer(2, GL_FLOAT, 6 * sizeof(float), 2, 8 * sizeof(float));

    program->setUniformValue("MVP", mvp);
}

void PreviewPane::SetupTexture()
{
}

void PreviewPane::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        wheelValue *= zoomFactor;

        if(wheelValue > 100.0f)
        {
            wheelValue = 100.0f;
        }
    }
    else
    {
        wheelValue *= (1.0f / zoomFactor);
        if(wheelValue < 0.01f)
        {
            wheelValue = 0.01f;
        }
    }

    // wheelValue += event->pixelDelta().y() / 100.0f;
}

void PreviewPane::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        panX += static_cast<float>(event->globalX() - oldX) / 1000.0f;
        panY -= static_cast<float>(event->globalY() - oldY) / 1000.0f;
    }

    oldX = event->globalX();
    oldY = event->globalY();
}

void PreviewPane::SetTexture(int width, int height, unsigned short *imageData)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, imageData);

    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        qDebug() << "2 OpenGL error: " << err;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR_MIPMAP_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    while((err = glGetError()) != GL_NO_ERROR)
    {
        qDebug() << "3 OpenGL error: " << err;
    }
}

void PreviewPane::SwitchRedChannel(bool enabled)
{
    redChannel = enabled;
}

void PreviewPane::SwitchGreenChannel(bool enabled)
{
    greenChannel = enabled;
}

void PreviewPane::SwitchBlueChannel(bool enabled)
{
    blueChannel = enabled;
}

bool PreviewPane::IsInitialized()
{
    return isValid();
}

void PreviewPane::SetImage(OCImage &image)
{
    imageWidth = static_cast<int>(image.Width());
    imageHeight = static_cast<int>(image.Height());

    glBindTexture(GL_TEXTURE_2D, textureRed);
    SetTexture(imageWidth, imageHeight, static_cast<unsigned short *>(image.RedChannel()));
    glBindTexture(GL_TEXTURE_2D, textureGreen);
    SetTexture(imageWidth, imageHeight, static_cast<unsigned short *>(image.GreenChannel()));
    glBindTexture(GL_TEXTURE_2D, textureBlue);
    SetTexture(imageWidth, imageHeight, static_cast<unsigned short *>(image.BlueChannel()));
}

void PreviewPane::EnableRendering(bool enable)
{
    _renderingEnabled = enable;

    if(_renderingEnabled)
    {
        this->update();
    }
}
