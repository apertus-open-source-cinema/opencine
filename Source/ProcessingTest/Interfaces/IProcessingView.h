#ifndef IPROCESSINGVIEW_H
#define IPROCESSINGVIEW_H

#include <QWidget>

#include <Image/OCImage.h>

using namespace OC::DataProvider;

class IProcessingView : public QWidget
{
public:
	virtual void SetFrame(OCImage& image) = 0;
	virtual void SetThumbnail(unsigned int width, unsigned int height, unsigned char* data) = 0;
};

#endif //IPROCESSINGVIEW_H
