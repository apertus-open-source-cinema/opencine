#include "LauncherLayout.h"
#include "ui_LauncherLayout.h"

LauncherLayout::LauncherLayout(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LauncherLayout)
{
	ui->setupUi(this);
}

LauncherLayout::~LauncherLayout()
{
	delete ui;
}