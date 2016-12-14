#pragma once
#include <QStyledItemDelegate>

class TaskProgressDelegate : public QStyledItemDelegate
{
	Q_OBJECT

	QFont font;
	QFont subFont ;

public:
	TaskProgressDelegate(QWidget* parent = Q_NULLPTR);
	~TaskProgressDelegate();

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
