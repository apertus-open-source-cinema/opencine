#pragma once
#include <QStyledItemDelegate>

class TaskProgressDelegate : public QStyledItemDelegate
{
	Q_OBJECT

	Q_PROPERTY(QString taskDescription READ GetTaskDescription WRITE SetTaskDescription)

	mutable QString _taskDescription;

public:
	TaskProgressDelegate(QWidget* parent = Q_NULLPTR);
	~TaskProgressDelegate();

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	QString GetTaskDescription() const;
	void SetTaskDescription(QString description);
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
};
