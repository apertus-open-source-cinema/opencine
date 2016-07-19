#ifndef IVIEW_H
#define IVIEW_H

#include <QWidget>


class IView : public QWidget
{
    Q_OBJECT

public:
    virtual ~IView() {}
};

#endif //IVIEW_H
