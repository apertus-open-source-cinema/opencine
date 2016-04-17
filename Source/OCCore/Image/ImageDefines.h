#ifndef IMAGEDEFINES_H
#define IMAGEDEFINES_H

namespace OC
{
	namespace DataProvider
	{
		enum class SourceFormat
		{
			Integer12 = 12,
			Integer14 = 14
		};

		enum class ImageFormat
		{
			Unknown,
			Integer12 = 12,
			Integer16 = 16
		};

		enum class ImageType
		{
			Unknown,
			Bayer
		};

		enum class FileFormat
		{
			Unknown,
			TIFF,
			DNG,
			CinemaDNG
		};
	}
}
#endif //IMAGEDEFINES_H
