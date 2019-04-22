// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCui
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <unordered_map>

#include <QDialog>
#include <QStandardItemModel>

#include "Task/ITask.h"

#include "OCui_export.h"

namespace Ui
{
    class ProgressDialog;
}

class OCUI_EXPORT ProgressDialog : public QDialog
{
    Q_OBJECT

    QStandardItemModel *_model;

    std::unordered_map<unsigned int, unsigned int> _taskMap; // task ID, row index
    unsigned int _indexCount; // Used for _taskMap, correct increment or decrement has to be ensured

public:
    explicit ProgressDialog(QWidget *parent = 0 /*, IDataTransfer* dataTransfer = nullptr*/);
    ~ProgressDialog();

    // TODO: Create interface for class and also consider to use some sort of proxy for tasks
    void AddTask(ITask *taskProgress);

    void SetTaskProgress(ITask *task);

private:
    Ui::ProgressDialog *ui;

private slots:
    void ProgressChanged(int) const;
};

#endif // PROGRESSDIALOG_H
