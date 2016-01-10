#ifndef IPROCESSINGVIEW_H
#define IPROCESSINGVIEW_H

#include <QWidget>

#include <Image/OCImage.h>

using namespace OC::DataProvider;

class IProcessingView : public QWidget
{
public:
    virtual void SetFrame(OCImage& image) = 0;
};

#endif //IPROCESSINGVIEW_H
