#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void SetLayout(QWidget& widget);

private:
	Ui::MainWindow *ui;

	QVBoxLayout* _layout;
};

#endif // MAINWINDOW_H
