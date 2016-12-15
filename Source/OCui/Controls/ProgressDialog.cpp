#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

#include "TaskProgressDelegate.h"

ProgressDialog::ProgressDialog(QWidget* parent/*, IDataTransfer* dataTransfer*/) :
	QDialog(parent),
	ui(new Ui::ProgressDialog)
{
	ui->setupUi(this);

	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	//setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	setModal(true);

	ui->listView->setItemDelegate(new TaskProgressDelegate());
	_model = new QStandardItemModel();
	ui->listView->setModel(_model); //connect the model to view.
}

ProgressDialog::~ProgressDialog()
{
	delete ui;
}

void ProgressDialog::AddTask(ITaskProgress* taskProgress) const
{
	// TODO: Replace by adequate data struct, so the data is compact and intuitive to use in delegate
	QStandardItem* item = new QStandardItem();
	QString taskDescription = QString::fromStdString(taskProgress->GetTaskDescription());
	QString subTaskDescription = QString::fromStdString(taskProgress->GetSubTaskDescription());
	QStringList values;
	values.push_back(taskDescription);
	values.push_back(subTaskDescription);
	values.push_back("0");

	item->setData(values, Qt::DisplayRole);
	_model->appendRow(item);
}

void ProgressDialog::SetTaskProgress(int taskIndex, int progress)
{
	QStandardItem* item = _model->item(0, 0);//new QStandardItem();
	//QString taskDescription = "";// QString::fromStdString(taskProgress->GetTaskDescription());
	//QString subTaskDescription = ""; //QString::fromStdString(taskProgress->GetSubTaskDescription());
	QStringList values = item->model()->data(item->index()).toStringList();
	//values.push_back(taskDescription);
	//values.push_back(subTaskDescription);
	values.replace(2, QString::number(progress));

	item->setData(values, Qt::DisplayRole);
//	_model->appendRow(item);
}

void ProgressDialog::ProgressChanged(int currentProgress) const
{
	ui->progressBar->setValue(currentProgress);
	//ui->label->setText(QString("File ") + std::to_string(currentProgress).c_str());
}
