// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "ProcessingView.h"
#include "ui_ProcessingView.h"

#include <fstream>
#include <thread>

#include <QFile>
#include <QPainter>
#include <QImage>
#include <QTimer>

#include "Controls/PreviewPane.h"

ProcessingView::ProcessingView(QWidget *parent) :
	thumbnailImage(nullptr),
	ui(new Ui::ProcessingView)
{
	ui->setupUi(this);

	ui->widget->installEventFilter(this);

    connect(ui->openFileButton, SIGNAL(clicked()), this, SIGNAL(OpenRAWFile()));
    connect(ui->debayerMethods, SIGNAL(currentIndexChanged(int)), this, SIGNAL(DebayerMethodChanged(int)));
}

ProcessingView::~ProcessingView()
{
	delete ui;
}

//char bayerMatrixRGGB[2][2] = { {0, 1}, {1, 2} };

//bool init = false;

void ProcessingView::paintEvent(QPaintEvent *)
{
	if (ui->openGLWidget->isValid() && testImage != nullptr)
	{
        ui->openGLWidget->SetImage(*testImage);
	}
}

void ProcessingView::SetFrame(OCImage &image)
{
	testImage = &image;
}

void ProcessingView::SetThumbnail(unsigned int width, unsigned int height, unsigned char* data)
{
	thumbnailImage = new QImage(data, width, height, QImage::Format_RGB888);
	*thumbnailImage = thumbnailImage->scaled(ui->widget->width(), ui->widget->height(), Qt::KeepAspectRatio);
}

void ProcessingView::LoadTexture()
{
	int i = 0;
}

bool ProcessingView::eventFilter(QObject *, QEvent *)
{
	QPainter painter(ui->widget);
	QPoint po(0, 0);

	if (thumbnailImage != nullptr)
	{
		painter.drawImage(po, *thumbnailImage);
	}

	return true;
}

void ProcessingView::on_pushButton_toggled(bool checked)
{
	ui->openGLWidget->SwitchRedChannel(checked);
}

void ProcessingView::on_pushButton_3_toggled(bool checked)
{
	ui->openGLWidget->SwitchGreenChannel(checked);
}

void ProcessingView::on_pushButton_4_toggled(bool checked)
{
    ui->openGLWidget->SwitchBlueChannel(checked);
}

void ProcessingView::EnableRendering(bool enable)
{
    ui->openGLWidget->EnableRendering(enable);
}

void ProcessingView::SetAvailableDebayerMethods(QStringList debayerMethods)
{
    ui->debayerMethods->addItems(debayerMethods);
    ui->debayerMethods->setCurrentIndex(0);
}
