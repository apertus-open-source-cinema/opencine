#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsPixmapItem* it;

    //LibRaw* imageProcessor;

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void SelectImportFolder();

public slots:
    void PlayImages();
};

#endif // MAINWINDOW_H
