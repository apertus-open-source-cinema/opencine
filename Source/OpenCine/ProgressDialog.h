#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>

#include "IDataTransfer.h"

namespace Ui {
class ProgressDialog;
}

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = 0, IDataTransfer* dataTransfer = nullptr);
    ~ProgressDialog();

private:
    Ui::ProgressDialog *ui;

private slots:
    void ProgressChanged(int);
};

#endif // PROGRESSDIALOG_H
