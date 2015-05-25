#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

ProgressDialog::ProgressDialog(QWidget *parent, IDataTransfer* dataTransfer) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->SourcePathLabel->setText("Source: " + dataTransfer->GetSourcePath());
    ui->TargetPathLabel->setText("Target: " + dataTransfer->GetTargetPath());

    connect(dataTransfer, SIGNAL(ProgressChanged(int)), SLOT(ProgressChanged(int)));
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::ProgressChanged(int currentProgress)
{
    ui->progressBar->setValue(currentProgress);
    //ui->label->setText("File " + std::to_string(currentProgress).c_str());
}
