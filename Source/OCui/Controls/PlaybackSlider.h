// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCui
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef PLAYBACKSLIDER_H
#define PLAYBACKSLIDER_H

#include <QWidget>

//#include <QtAV/QtAV>
//#include <QtAVWidgets/QtAVWidgets>

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

    void LoadFile(QString filePath);

private:
	Ui::PlaybackSlider *ui;
	bool _advancedMode;

    //QtAV::AVPlayer* player;

    void SetupPlayer();

	private slots:
    void OnPlayButtonToggled(bool toggled);

    void OnStopClicked();

    void PrevFrame();
    void NextFrame();

private slots:
    void PauseAfterLoad();
    void UpdateSlider(qint64 currentPos);

    void OnJumpStartClicked();
    void OnJumpEndClicked();
};

#endif //PLAYBACKSLIDER_H

