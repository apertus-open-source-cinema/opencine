// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCui
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#pragma once
#include <QStyledItemDelegate>
#include <qprogressbar.h>

class TaskProgressDelegate : public QStyledItemDelegate
{
	Q_OBJECT

	QFont font;
	QFont subFont;
	QFontMetrics* _fontMetrics;

	QProgressBar* _progressBar;	

public:
	TaskProgressDelegate(QWidget* parent = Q_NULLPTR);
	~TaskProgressDelegate();

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
