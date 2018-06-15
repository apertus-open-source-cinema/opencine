// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef PREVIEWPANE_H
#define PREVIEWPANE_H

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include <Image/OCImage.h>

class PreviewPane : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
	QMatrix4x4 mvp;

    bool redChannel = true;
    bool greenChannel = true;
    bool blueChannel = true;

    float viewWidth = 1;
    float viewHeight = 1;
    int imageWidth = 1;
    int imageHeight = 1;

    int oldX = 0;
    int oldY = 0;

    float panX = 0.0;
    float panY = 0.0;

    float wheelValue = 1.0;
    float zoomFactor = 1.1f;

    // Texture IDs
    GLuint textureRed = 0;
    GLuint textureGreen = 0;
    GLuint textureBlue = 0;

    bool _renderingEnabled;

public:
	PreviewPane(QWidget *parent = 0);
	~PreviewPane();

	void SwitchRedChannel(bool enabled);
	void SwitchGreenChannel(bool enabled);
	void SwitchBlueChannel(bool enabled);

	bool IsInitialized();

    void SetImage(OC::DataProvider::OCImage& image);

    void EnableRendering(bool enable);

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void printVersionInformation();

    void SetTexture(int width, int height, unsigned short* imageData);

private:
	void SetupShaders();
	void SetupVertexBuffer();
	void SetupObject();
	void SetupTexture();

	QOpenGLShaderProgram* program;
	QOpenGLBuffer vertex;
	QOpenGLVertexArrayObject object;

	bool _initialized;

	// QWidget interface
protected:
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // PREVIEWPANE_H
