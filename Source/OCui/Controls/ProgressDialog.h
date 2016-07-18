#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>

#include "OCui_export.h"

//#include "IDataTransfer.h"

namespace Ui {
class ProgressDialog;
}

class OCUI_EXPORT ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = 0/*, IDataTransfer* dataTransfer = nullptr*/);
    ~ProgressDialog();

private:
    Ui::ProgressDialog *ui;

private slots:
    void ProgressChanged(int);
};

#endif // PROGRESSDIALOG_H
