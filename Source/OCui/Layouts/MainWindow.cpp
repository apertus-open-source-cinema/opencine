#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetLayout(QWidget &widget)
{
     //ui->mainPane->setAttribute(Qt::WA_OpaquePaintEvent);

     //ui->mainPane->setAttribute(Qt::WA_NoSystemBackground);

    ui->mainPane->addWidget(&widget);

    //widget.showFullScreen();
    //this->adjustSize();
}
