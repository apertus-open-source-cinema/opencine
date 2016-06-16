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

		OCImage* testImage = nullptr;
	QImage* thumbnailImage;

public:
	explicit ProcessingView(QWidget *parent = nullptr);
	~ProcessingView();

	virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

	void SetFrame(OCImage& image) override;

	void SetThumbnail(unsigned int width, unsigned int height, unsigned char* data) override;

	private slots:
	void on_pushButton_toggled(bool checked);

	void on_pushButton_3_toggled(bool checked);

	void on_pushButton_4_toggled(bool checked);

private:
	Ui::ProcessingView *ui;

	void LoadTexture();

	// QObject interface
public:
	bool eventFilter(QObject *, QEvent *) override;
};

#endif // PROCESSINGVIEW_H
