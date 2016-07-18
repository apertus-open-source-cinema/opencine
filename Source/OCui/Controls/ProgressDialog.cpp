#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

#include "TaskProgressDelegate.h"

#include <QStandardItemModel>

ProgressDialog::ProgressDialog(QWidget *parent/*, IDataTransfer* dataTransfer*/) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

	ui->listView->setItemDelegate(new TaskProgressDelegate());
	//ui->listWidget->addItem("ABCDEF098");
	QStandardItemModel* model = new QStandardItemModel();
	ui->listView->setModel(model);//connect the model to view.
	QStandardItem *item = new QStandardItem();
	item->setData("Inbox");
	QStandardItem *item2 = new QStandardItem();
	item2->setData("Sent");
	
	model->appendRow(item);
	model->appendRow(item2);
    
	//ui->SourcePathLabel->setText("Source: " + dataTransfer->GetSourcePath());
    //ui->TargetPathLabel->setText("Target: " + dataTransfer->GetTargetPath());

    //connect(dataTransfer, SIGNAL(ProgressChanged(int)), SLOT(ProgressChanged(int)));

    //ui->progressBar->setMaximum(dataTransfer->GetCount());
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::ProgressChanged(int currentProgress)
{
    ui->progressBar->setValue(currentProgress);
    ui->label->setText(QString("File ") + std::to_string(currentProgress).c_str());
}
