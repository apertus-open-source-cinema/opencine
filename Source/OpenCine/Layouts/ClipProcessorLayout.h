#ifndef CLIPPROCESSORLAYOUT_H
#define CLIPPROCESSORLAYOUT_H

#include <QWidget>

#include "Context.h"

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
    OCContext* _context;
};

#endif // CLIPPROCESSORLAYOUT_H
