#ifndef IPROCESSINGVIEW_H
#define IPROCESSINGVIEW_H

#include <QWidget>

#include <API/IDataProvider.h>

using namespace OC::DataProvider;

class IProcessingView : public QWidget
{
    virtual void SetFrame(Image& image) = 0;
};

#endif //IPROCESSINGVIEW_H
