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
    button->setGeometry(0, 0, button->rect().height(), button->rect().height());
    button->setText(name);

    QPixmap pixmap("./Resources/Launcher/" + imagePath);
    QIcon buttonIcon(pixmap);
    button->setIcon(buttonIcon);
    button->setIconSize(QSize(button->rect().height(), button->rect().height()));

    //button->setIconSize(pixmap.rect().size());

    ui->buttonPane->addWidget(button);
}
