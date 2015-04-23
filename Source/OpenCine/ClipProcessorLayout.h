#ifndef CLIPPROCESSORLAYOUT_H
#define CLIPPROCESSORLAYOUT_H

#include <Context.h>
#include <QWidget>

namespace Ui {
class ClipProcessorLayout;
}

class ClipProcessorLayout : public QWidget
{
    Q_OBJECT

public:
    explicit ClipProcessorLayout(QWidget *parent = 0, const OCContext& context = OCContext());
    ~ClipProcessorLayout();

private:
    Ui::ClipProcessorLayout *ui;
};

#endif // CLIPPROCESSORLAYOUT_H
