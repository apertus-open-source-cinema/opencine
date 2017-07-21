// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCLauncher
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "LauncherView.h"
#include "ui_LauncherView.h"

#include <QToolButton>

LauncherView::LauncherView(QWidget *parent) :
    ui(new Ui::LauncherView)
{
    ui->setupUi(this);
}

LauncherView::~LauncherView()
{
    delete ui;
}

void LauncherView::SetButtonList(std::vector<ApplicationInfo> list)
{
    for(ApplicationInfo info : list)
    {
        InsertButton(info.Name, info.ImagePath);
    }
}

void LauncherView::InsertButton(QString name, QString imagePath)
{
    QToolButton* button = new QToolButton();

    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    button->setFixedSize(180,180);
    button->setText(name);

    QPixmap pixmap("./Resources/Launcher/" + imagePath);
    QIcon buttonIcon(pixmap);
    button->setIcon(buttonIcon);

    button->setIconSize(QSize(button->rect().height() * 0.8, button->rect().height() * 0.8));

    ui->buttonPane->addWidget(button);
}
