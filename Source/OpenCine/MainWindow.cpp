#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QItemDelegate>
#include <QStandardItemModel>
#include <QPainter>

#include "ClipInformationItem.h"

class ClipInformationModel : public QAbstractListModel
{
public:
  ClipInformationModel(QObject * parent = 0);
  ~ClipInformationModel();

  int rowCount(const QModelIndex & parent = QModelIndex()) const;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  std::vector<ClipInformationItem*> clipItemList;

  // QAbstractItemModel interface
public:
  bool insertRows(int row, int count, const QModelIndex &parent);
  bool setData(const QModelIndex &index, const QVariant &value, int role);
};

/*
  \class MyListModel
*/
ClipInformationModel::ClipInformationModel(QObject * parent)
  : QAbstractListModel(parent)
{
}

ClipInformationModel::~ClipInformationModel()
{
}

int ClipInformationModel::rowCount(const QModelIndex & parent) const
{
  return 35;
}

QVariant ClipInformationModel::data(const QModelIndex & index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (role == Qt::DisplayRole)
  {
    const QString s = QString("Clip %1").arg(index.row());
    return s;
  }

  return QVariant();
}

bool ClipInformationModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);
    endInsertRows();
}

bool ClipInformationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    clipItemList.push_back((ClipInformationItem*)value.data());
}

/*
  \class MyCustomListViewItem
*/
class MyCustomListViewItemDelegate : public QItemDelegate
{
public:
  MyCustomListViewItemDelegate(QObject * parent = 0);
  ~MyCustomListViewItemDelegate();
  virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
  virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

protected:
  ClipInformationItem* _itemWidget;
};

/*
  \class MyCustomListViewItemDelegate
*/
MyCustomListViewItemDelegate::MyCustomListViewItemDelegate(QObject * parent)
  : QItemDelegate(parent)
    ,_itemWidget(new ClipInformationItem())
{
}

MyCustomListViewItemDelegate::~MyCustomListViewItemDelegate()
{
  if (_itemWidget)
  {
    delete _itemWidget;
    _itemWidget = NULL;
  }
}

void MyCustomListViewItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  _itemWidget->resize(option.rect.size());

  // Update data of widget here.
  const QString s = index.data().toString();
  const QString s2 = QString("In detail it means %1").arg(s);
  _itemWidget->SetFilename(s.toStdString());
  //_itemWidget->_ui.labelDescription->setText(s2);
  //_itemWidget->_ui.progressBar->setValue( index.row() * 2 );

  // Change the background color of the widget if it is selected.
  QPalette pal;
  if ((option.state & QStyle::State_Selected) == QStyle::State_Selected)
  {
    pal.setBrush(QPalette::Window, QBrush(QColor(Qt::lightGray)));
  }
  else
  {
    pal.setBrush(QPalette::Window, QBrush(QColor(Qt::transparent)));
  }
  _itemWidget->setPalette(pal);

  // Paint the widget now.
  painter->save();
  painter->translate(option.rect.topLeft());
  _itemWidget->render(painter);
  painter->restore();
}

QSize MyCustomListViewItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  const int width = _itemWidget->minimumWidth();
  const int height = _itemWidget->height();
  return QSize(width, height);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create test data
    //QStringListModel* model = new QStringListModel(this);
    //QStringList clipList;
    //clipList << "Clip 1" << "Clip 2" << "Clip 3";
    //model->setStringList(clipList);

    ClipInformationModel* model = new ClipInformationModel(this);
    ClipInformationItem* widget = new ClipInformationItem();
    ClipInformationItem* widget2 = new ClipInformationItem();

    ui->listView->setItemDelegate(new MyCustomListViewItemDelegate());


    QPixmap p("./clouds.jpg");
    // get label dimensions
    int w = ui->previewArea->width() * 10;
    int h = ui->previewArea->height() * 10;

    // set a scaled pixmap to a w x h window keeping its aspect ratio
    ui->previewArea->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));

    //model->insertRows(0, 0, QModelIndex());
    //QModelIndex index = model->index(0, 0, QModelIndex());
    //model->setData(index, widget);
//

    //model->appendRow(widget2);

//    model->insertRows(5, 7, QModelIndex());

//        for (int row = 5; row < 12; ++row) {
//            QModelIndex index = model->index(row, 0, QModelIndex());
//            model->setData(index, QString::number(row+1));
//        }


    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
