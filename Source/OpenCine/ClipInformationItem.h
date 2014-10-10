#ifndef CLIPINFORMATIONITEM_H
#define CLIPINFORMATIONITEM_H

#include <QWidget>

namespace Ui {
class ClipInformationItem;
}

class ClipInformationItem : public QWidget
{
    Q_OBJECT

public:
    explicit ClipInformationItem(QWidget* parent = 0);
    ~ClipInformationItem();

    void SetFilename(std::string fileName);

private:
    Ui::ClipInformationItem* ui;
};

#endif // CLIPINFORMATIONITEM_H
