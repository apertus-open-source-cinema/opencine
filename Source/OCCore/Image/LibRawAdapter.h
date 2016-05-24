#ifndef LIBRAWADAPTER_H
#define LIBRAWADAPTER_H

#include <libraw.h>

#include "IImageLoader.h"

namespace OC
{
	namespace DataProvider 
	{
		class LibRawAdapter : public IImageLoader
		{
		};
	}
}

#endif //LIBRAWADAPTER_H
