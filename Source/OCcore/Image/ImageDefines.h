// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef IMAGEDEFINES_H
#define IMAGEDEFINES_H

#include <unordered_map>

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
            Integer14 = 14,
            Integer16 = 16
        };

        enum class ImageType
        {
            Unknown,
            Bayer
        };

        enum class FileFormat : size_t
        {
            Unknown,
            TIFF,
            DNG,
            CinemaDNG,
            MLV
        };

        struct FileFormatHash
        {
            template <typename T>
            std::size_t operator()(T t) const
            {
                return static_cast<std::size_t>(t);
            }
        };

        inline std::unordered_map<int, std::string> CreateTIFFTagMap()
        {
            std::unordered_map<int, std::string> tagNames;
            tagNames.insert(std::pair<int, std::string>(256, "ImageWidth"));

            return tagNames;
        }
    }
}
#endif //IMAGEDEFINES_H
