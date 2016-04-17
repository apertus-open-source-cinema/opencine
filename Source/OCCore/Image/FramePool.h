#ifndef FRAMEPOOL_H
#define FRAMEPOOL_H

#include <unordered_map>

#include <Image\OCImage.h>

namespace OC
{
	namespace DataProvider
	{
		class FramePool final
		{
			std::unordered_map<std::string, OCImage*> _pool;

		public:
			~FramePool()
			{
				/*for (OCImage* image : _pool)
				{
					delete image;
				}*/
			}

			OCImage* AddNewImage(unsigned int byteSize)
			{
				OCImage* image = new OCImage();
				_pool.insert(std::make_pair("Test", image));
			}
		};
	}
}

#endif //FRAMEPOOL_H

