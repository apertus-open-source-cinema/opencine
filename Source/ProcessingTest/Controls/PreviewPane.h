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

class PreviewPane : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
	QMatrix4x4 mvp;

    bool redChannel = true;
    bool greenChannel = true;
    bool blueChannel = true;

public:
	PreviewPane(QWidget *parent = 0);
	~PreviewPane();

	void SetTextureRed(int width, int height, unsigned short* imageData);
	void SetTextureGreen(int width, int height, unsigned short* imageData);
	void SetTextureBlue(int width, int height, unsigned short* imageData);

	void SwitchRedChannel(bool enabled);
	void SwitchGreenChannel(bool enabled);
	void SwitchBlueChannel(bool enabled);

	bool IsInitialized();

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void printVersionInformation();
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
