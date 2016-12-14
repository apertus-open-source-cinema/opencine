#ifndef PLAYBACKSLIDER_H
#define PLAYBACKSLIDER_H

#include <QWidget>

#include "OCui_export.h"

namespace Ui {
	class PlaybackSlider;
}

class OCUI_EXPORT PlaybackSlider : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(bool advancedMode READ AdvancedMode WRITE SetAdvancedMode)

public:
	explicit PlaybackSlider(QWidget *parent = 0);
	~PlaybackSlider();

	void SetupEvents();

	bool AdvancedMode()
	{
		return _advancedMode;
	}

	void SetAdvancedMode(bool advancedMode)
	{
		_advancedMode = advancedMode;
	}

private:
	Ui::PlaybackSlider *ui;
	bool _advancedMode;

	private slots:
	//void OnSessionChanged(OCSession* session);
	//void OnFrameChanged(unsigned int frameNumber, OCFrame* frame);
	//void OnSliderMoved(int frameNumber);

	//void OnPlayButtonToggled(bool toggled);
	//void OnPlayRevButtonToggled(bool toggled);

	//void OnStopClicked();
};

#endif //PLAYBACKSLIDER_H
