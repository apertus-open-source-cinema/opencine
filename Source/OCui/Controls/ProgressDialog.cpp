// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCui
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

#include "TaskProgressDelegate.h"

#include "Log/Logger.h"

ProgressDialog::ProgressDialog(QWidget* parent /*, IDataTransfer* dataTransfer*/) :
        QDialog(parent),
        ui(new Ui::ProgressDialog),
        _indexCount(0)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setModal(true);

    ui->listView->setItemDelegate(new TaskProgressDelegate());
    _model = new QStandardItemModel();
    ui->listView->setModel(_model); // connect the model to view.
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::AddTask(ITask* task)
{
    // TODO: Replace by adequate data struct, so the data is compact and intuitive to use in delegate
    QStandardItem* item = new QStandardItem();
    QString taskDescription = QString::fromStdString(task->GetTaskDescription());
    QString subTaskDescription = QString::fromStdString(task->GetSubTaskDescription());
    QStringList values;
    values.push_back(taskDescription);
    values.push_back(subTaskDescription);
    values.push_back("0");

    item->setData(values, Qt::DisplayRole);
    _model->appendRow(item);

    _taskMap.insert(std::make_pair(task->GetID(), _indexCount));
    _indexCount++;
}

void ProgressDialog::SetTaskProgress(ITask* task)
{
    auto it = _taskMap.find(task->GetID());

    if(it == _taskMap.end())
    {
        OC_LOG_WARNING("Task " + std::to_string(task->GetID()) + "not found");
        return;
    }


    QStandardItem* item = _model->item(static_cast<int>((*it).second), 0); // new QStandardItem();
    // qDebug("Task row: " + QString::number(static_cast<int>((*it).second)).toLatin1());
    QString taskDescription = QString::fromStdString(task->GetTaskDescription());
    QString subTaskDescription = QString::fromStdString(task->GetSubTaskDescription());
    QStringList values = item->model()->data(item->index()).toStringList();
    values.replace(0, taskDescription);
    values.replace(1, subTaskDescription);
    values.replace(2, QString::number(task->GetProgressPercentage()));

    item->setData(values, Qt::DisplayRole);
}

void ProgressDialog::ProgressChanged(int currentProgress) const
{
    ui->progressBar->setValue(currentProgress);
}
