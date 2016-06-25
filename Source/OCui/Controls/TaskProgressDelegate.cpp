#include "TaskProgressDelegate.h"

#include <QApplication>
#include <QPainter>
#include <QProgressBar>

TaskProgressDelegate::TaskProgressDelegate(QWidget * parent) : QStyledItemDelegate(parent)
{
}

TaskProgressDelegate::~TaskProgressDelegate()
{
}

QSize TaskProgressDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	//QIcon icon = qvariant_cast<QIcon>(index.data(IconRole));
	//QSize iconsize = icon.actualSize(option.decorationSize);
	QFont font = QApplication::font();
	QFontMetrics fm(font);

	return QSize(200, 70);// (QSize(iconsize.width(), iconsize.height() + fm.height() + 8));

}

void TaskProgressDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QStyledItemDelegate::paint(painter, option, index);

	painter->save();

	QFont font = QApplication::font();
	QFont subFont = QApplication::font();
	//font.setPixelSize(font.weight()+);
	font.setBold(true);
	subFont.setWeight(subFont.weight() - 5);
	subFont.setPointSize(8);
	QFontMetrics fm(font);

	//QIcon icon = qvariant_cast<QIcon>(index.data(IconRole));
	QString headerText = qvariant_cast<QString>("Test123");
	QString subText = qvariant_cast<QString>("SubText123");

	//QSize iconsize = icon.actualSize(option.decorationSize);

	QRect headerRect = option.rect;
	headerRect.setBottom(headerRect.bottom() / 2);
	QRect subheaderRect = option.rect;
	QRect iconRect = subheaderRect;

	//iconRect.setRight(iconsize.width() + 30);
	//iconRect.setTop(iconRect.top() + 5);
	headerRect.setLeft(10);
	subheaderRect.setLeft(10);
	subheaderRect.setTop(headerRect.bottom() + 10);
	headerRect.setTop(headerRect.top() + 10);
	headerRect.setBottom(headerRect.top() + fm.height());

	subheaderRect.setTop(headerRect.bottom() + 2);

	//painter->drawPixmap(QPoint(iconRect.right()/2,iconRect.top()/2),icon.pixmap(iconsize.width(),iconsize.height()));
	//painter->drawPixmap(QPoint(iconRect.left() + iconsize.width() / 2 + 2, iconRect.top() + iconsize.height() / 2 + 3), icon.pixmap(iconsize.width(), iconsize.height()));

	painter->setFont(font);
	painter->drawText(headerRect, headerText);


	painter->setFont(subFont);
	painter->drawText(subheaderRect.left(), subheaderRect.top() + 17, subText);

	painter->save();
	painter->translate(option.rect.width() / 5, option.rect.y() + option.rect.height() / 2);
	QProgressBar renderer;
	renderer.resize(option.rect.size().width() / 5 * 4 - 10, option.rect.size().height());
	renderer.setValue(35);
	
	renderer.render(painter);

	painter->restore();
}
