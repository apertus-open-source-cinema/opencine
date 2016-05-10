#pragma once
#include <QStyledItemDelegate>

class TaskProgressDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	TaskProgressDelegate(QWidget * parent = Q_NULLPTR);
	~TaskProgressDelegate();

	QSize sizeHint(const QStyleOptionViewItem &  option, const QModelIndex & index) const;

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
};
