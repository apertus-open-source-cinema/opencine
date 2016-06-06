#ifndef FRAMEPOOL_H
#define FRAMEPOOL_H

#include <unordered_map>

//#include <Image\OCImage.h>
#include <MemoryPool.h>

namespace OC
{
	namespace DataProvider
	{
		//template <typename T, size_t BlockSize = 4096>
		//class FramePool<size_t> : public MemoryPool<size_t>
		//{
		//	std::unordered_map<std::string, OCImage*> _pool;

		//public:
		//	~FramePool()
		//	{
		//		/*for (OCImage* image : _pool)
		//		{
		//			delete image;
		//		}*/
		//	}

		//	OCImage* AddNewImage(unsigned int byteSize)
		//	{
		//		OCImage* image = new OCImage();
		//		_pool.insert(std::make_pair("Test", image));
		//		
		//		return nullptr;
		//	}
		//};
	}
}

#endif //FRAMEPOOL_H

