#include "TaskProgressDelegate.h"

#include <QApplication>
#include <QPainter>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QLabel>

TaskProgressDelegate::TaskProgressDelegate(QWidget* parent) : QStyledItemDelegate(parent),
                                                              font(QApplication::font()),
                                                              subFont(QApplication::font())
{
	font.setBold(true);
	subFont.setPointSize(font.pointSize() - 2);
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

	QFontMetrics fm(font);

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
	headerRect.setWidth(fm.width(headerText + " | "));
	headerRect.setBottom(headerRect.top() + fm.height() + 5);

	QRect subheaderRect = option.rect;
	subheaderRect.setTop(subheaderRect.top() + fm.height() / 2);
	subheaderRect.setLeft(headerRect.width() + 10);

	painter->setFont(font);
	painter->drawText(headerRect, headerText + " | ");
	painter->setFont(subFont);
	painter->drawText(subheaderRect, subText);

	// Automatic layout, just for test atm
	//QWidget widgetTest;
	//QHBoxLayout layout;
	//layout.addWidget(new QLabel("Test1"));
	//layout.addWidget(new QLabel("Test2"));
	//widgetTest.setLayout(&layout);
	//widgetTest.render(painter, option.rect.topLeft());

	painter->translate(10, headerRect.bottom());


	// TODO: Replace by a new progress bar, which supports custom animations, e.g. for indeterminate state
	QProgressBar progressBar;
	progressBar.resize(option.rect.size().width() - 10, option.rect.size().height());
	progressBar.setValue(35);
	progressBar.render(painter);

	painter->restore();
}

QWidget* TaskProgressDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return nullptr;
}
