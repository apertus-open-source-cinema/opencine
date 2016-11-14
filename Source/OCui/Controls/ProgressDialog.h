#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>

#include "OCui_export.h"
#include <QStandardItemModel>
#include "Task/ITaskProgress.h"

//#include "IDataTransfer.h"

namespace Ui {
class ProgressDialog;
}

class OCUI_EXPORT ProgressDialog : public QDialog
{
	Q_OBJECT
		
	QStandardItemModel* _model;

public:
    explicit ProgressDialog(QWidget *parent = 0/*, IDataTransfer* dataTransfer = nullptr*/);
    ~ProgressDialog();

	// TODO: Create interface for class and also consider to use some sort of proxy for tasks
	void AddTask(ITaskProgress* taskProgress) const;

private:
    Ui::ProgressDialog *ui;

private slots:
    void ProgressChanged(int) const;
};

#endif // PROGRESSDIALOG_H
