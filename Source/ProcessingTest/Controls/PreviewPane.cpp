#include "PreviewPane.h"

#include <QWheelEvent>

unsigned char pixels[12] = {
    255,   0, 0,     0, 255,   0,
    0, 255, 0,     0,   0, 255
};

float xOffset = 0.5f / 4096.0f;
float yOffset = 0.5f / 3072.0f;

float wheelValue = 1.0;

// Create a colored triangle
static const float vertices[] = {
    -1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0, 0.0,
    -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0, 1.0,
    1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0, 0.0,
    1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0, 1.0
};

PreviewPane::PreviewPane(QWidget *parent) : QOpenGLWidget(parent),
    _initialized(false)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);

    //QSurfaceFormat format;
    //format.setVersion(3, 3);
    //format.setProfile(QSurfaceFormat::CoreProfile);
    //format.setDepthBufferSize(24);
    //format.setStencilBufferSize(8);
    //QSurfaceFormat::setDefaultFormat(format);
}

PreviewPane::~PreviewPane()
{
    delete program;
}

void PreviewPane::initializeGL()
{
    initializeOpenGLFunctions();

    printVersionInformation();

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    SetupShaders();
    SetupVertexBuffer();
    SetupObject();
    //SetupTexture();

    object.release();
    vertex.release();
    program->release();

    _initialized = true;
}

float viewWidth = 1;
float viewHeight = 1;
int imageWidth = 1;
int imageHeight = 1;

void PreviewPane::resizeGL(int w, int h)
{
    viewWidth = (float)w/ (float)h;
    //viewHeight = 1.0;
    //    QMatrix4x4 projection;
    //    projection.ortho(-1.0 - wheelValue, 1.0 + wheelValue, -0.1, 0.1, 0.01f, 1000.0f);
    //    QMatrix4x4 view;
    //    view.lookAt(QVector3D(0.0,0.0,-5.0), QVector3D(0.0,0.0,0.0), QVector3D(0.0,1.0,0.0));
    //    QMatrix4x4 model;
    //    model.setToIdentity();

    //    mvp = projection * view * model;
    //glLoadMatrixf(m_projection.data());
}

GLuint textureRed  = 0;
GLuint textureGreen = 0;
GLuint textureBlue = 0;

void PreviewPane::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    program->bind();
    {
        QMatrix4x4 projection;
        projection.ortho(-viewWidth / 2.0 * wheelValue, viewWidth / 2.0 * wheelValue, -viewHeight / 2.0 * wheelValue, viewHeight / 2.0 * wheelValue, 0.01f, 1000.0f);
        QMatrix4x4 view;
        view.lookAt(QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0));
        QMatrix4x4 model;
        model.setToIdentity();
        model.scale(float(imageWidth) / (float)imageHeight, 1.0f, 1.0f);

        mvp = projection * view * model;

        program->setUniformValue("MVP", mvp);

        object.bind();

        if(redChannel)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureRed);
            program->setUniformValue("texture1", 0);
        }
        else
        {
            program->setUniformValue("texture1", -1);
        }

        if(greenChannel)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, textureGreen);
            program->setUniformValue("texture2", 1);
        }
        else
        {
            program->setUniformValue("texture2", -1);
        }

        if(blueChannel)
        {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, textureBlue);
            program->setUniformValue("texture3", 2);
        }
        else
        {
            program->setUniformValue("texture3", -1);
        }

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
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile())
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
    //    glGenTextures(1, &texture);

    //    glBindTexture(GL_TEXTURE_2D, texture);

    //    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE16, 4096, 3072, 0, GL_LUMINANCE, GL_UNSIGNED_SHORT, nullptr);

    //    glGenerateMipmap(GL_TEXTURE_2D);

    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //    glBindTexture(GL_TEXTURE_2D, 0);
}

float zoomFactor = 1.1f;

void PreviewPane::wheelEvent(QWheelEvent* event)
{
    if(event->delta() < 0)
    {
        wheelValue *= zoomFactor;

        if(wheelValue > 100.0)
        {
            wheelValue = 100.0;
        }
    }
    else
    {
        wheelValue *= (1.0f / zoomFactor);
        if(wheelValue < 0.01)
        {
            wheelValue = 0.01;
        }
    }

    //wheelValue += event->pixelDelta().y() / 100.0f;





}

void PreviewPane::SetTextureRed(int width, int height, unsigned short* imageData)
{
    if(textureRed != 0)
    {
        return;
    }

    imageWidth = width;
    imageHeight = height;

    glGenTextures(1, &textureRed);

    glBindTexture(GL_TEXTURE_2D, textureRed);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, imageData);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        qDebug() << "2 OpenGL error: " << err;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_NEAREST); //GL_LINEAR_MIPMAP_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    while ((err = glGetError()) != GL_NO_ERROR)
    {
        qDebug() << "3 OpenGL error: " << err;
    }
}

void PreviewPane::SetTextureBlue(int width, int height, unsigned short* imageData)
{
    if(textureBlue != 0)
    {
        return;
    }

    glGenTextures(1, &textureBlue);

    glBindTexture(GL_TEXTURE_2D, textureBlue);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, imageData);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        qDebug() << "2 OpenGL error: " << err;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    while ((err = glGetError()) != GL_NO_ERROR)
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

void PreviewPane::SetTextureGreen(int width, int height, unsigned short* imageData)
{
    if(textureBlue != 0)
    {
        return;
    }

    glGenTextures(1, &textureGreen);

    glBindTexture(GL_TEXTURE_2D, textureGreen);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, imageData);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        qDebug() << "2 OpenGL error: " << err;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); //GL_LINEAR_MIPMAP_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    while ((err = glGetError()) != GL_NO_ERROR)
    {
        qDebug() << "3 OpenGL error: " << err;
    }
}

bool PreviewPane::IsInitialized()
{
    return isValid();
}
