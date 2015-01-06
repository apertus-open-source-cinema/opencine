#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

#include "Core/Context.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(OCContext* context, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsPixmapItem* it;

    OCContext* _context;
    //LibRaw* imageProcessor;

//protected:
    //void resizeEvent(QResizeEvent *);

private slots:
    //void SelectImportFolder();
    //void PlayImages();
    void on_aboutButton_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
