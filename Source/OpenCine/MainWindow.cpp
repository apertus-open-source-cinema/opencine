#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create test data
    QStringListModel* model = new QStringListModel(this);
    QStringList clipList;
    clipList << "Clip 1" << "Clip 2" << "Clip 3";
    model->setStringList(clipList);

    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
