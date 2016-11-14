#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

#include "TaskProgressDelegate.h"

ProgressDialog::ProgressDialog(QWidget *parent/*, IDataTransfer* dataTransfer*/) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

	ui->listView->setItemDelegate(new TaskProgressDelegate());
	//ui->listWidget->addItem("ABCDEF098");
	_model = new QStandardItemModel();
	ui->listView->setModel(_model);//connect the model to view.
	QStandardItem *item = new QStandardItem();
	item->setData("Inbox");
	QStandardItem *item2 = new QStandardItem();
	item2->setData("Sent");
	QStandardItem *item3 = new QStandardItem();
	item2->setData("Sent");
	
	//model->appendRow(item);
	//model->appendRow(item2);
	//model->appendRow(item3);
    
	//ui->SourcePathLabel->setText("Source: " + dataTransfer->GetSourcePath());
    //ui->TargetPathLabel->setText("Target: " + dataTransfer->GetTargetPath());

    //connect(dataTransfer, SIGNAL(ProgressChanged(int)), SLOT(ProgressChanged(int)));

    //ui->progressBar->setMaximum(dataTransfer->GetCount());
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::AddTask(ITaskProgress* taskProgress) const
{
	QStandardItem *item = new QStandardItem();
	QString taskDescription = QString::fromStdString(taskProgress->GetTaskDescription());
	item->setData(taskDescription);

	_model->appendRow(item);
}

void ProgressDialog::ProgressChanged(int currentProgress) const
{
    ui->progressBar->setValue(currentProgress);
    //ui->label->setText(QString("File ") + std::to_string(currentProgress).c_str());
}
