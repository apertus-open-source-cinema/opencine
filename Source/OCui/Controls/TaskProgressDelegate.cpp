#include "TaskProgressDelegate.h"

#include <QApplication>
#include <QPainter>
#include <QProgressBar>
#include <QHBoxLayout>

TaskProgressDelegate::TaskProgressDelegate(QWidget* parent) : QStyledItemDelegate(parent),
                                                              font(QApplication::font()),
                                                              subFont(QApplication::font())
{
	_progressBar = new QProgressBar();

	font.setBold(true);
	subFont.setPointSize(font.pointSize() - 2);
	_fontMetrics = new QFontMetrics(font);
}

TaskProgressDelegate::~TaskProgressDelegate()
{
}

QSize TaskProgressDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return QSize(option.rect.width(), 70);
}

void TaskProgressDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	// Draws default things, like focus rectangle
	QStyledItemDelegate::paint(painter, option, index);

	painter->save();

	QString headerText = "?";
	QString subText = "?";

	QStringList values = index.model()->data(index).toStringList();
	if (!values.empty())
	{
		headerText = values.at(0);
		subText = values.at(1);
	}

	QRect headerRect = option.rect;
	headerRect.setLeft(10);
	headerRect.setTop(headerRect.top() + 10);
	headerRect.setWidth(_fontMetrics->width(headerText + " | "));
	headerRect.setBottom(headerRect.top() + _fontMetrics->height() + 5);

	QRect subheaderRect = option.rect;
	subheaderRect.setTop(subheaderRect.top() + _fontMetrics->height() / 2);
	subheaderRect.setLeft(headerRect.width() + 10);

	painter->setFont(font);
	painter->drawText(headerRect, headerText + " | ");
	painter->setFont(subFont);
	painter->drawText(subheaderRect, subText);

	painter->translate(10, headerRect.bottom() + 10);

	// TODO: Replace by a new progress bar, which supports custom animations, e.g. for indeterminate state
	_progressBar->resize(option.rect.size().width() - 20, option.rect.size().height());
	_progressBar->setValue(values.at(2).toInt());
	_progressBar->render(painter);

	painter->restore();
}

QWidget* TaskProgressDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return nullptr;
}
