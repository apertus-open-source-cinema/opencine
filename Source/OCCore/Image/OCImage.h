#ifndef OCIMAGE_H
#define OCIMAGE_H

#include <cstring>
#include <fstream>

#include "ImageDefines.h"

namespace OC
{
    namespace DataProvider
    {
        class OCImage
        {
            unsigned int _width;
            unsigned int _height;
            //unsigned char* _data;

            ImageType _type;

            void* _redData;
            void* _greenData;
            void* _blueData;

            //unsigned int _dataSize;
            unsigned int _dataLength;
            ImageFormat _format;

        public:
            void SetWidth(unsigned int width)
            {
                _width = width;
            }

            void SetHeight(unsigned int height)
            {
                _height = height;
            }

            /*void SetData(unsigned char* data, unsigned int size)
            {
                _dataSize = size;

                _data = new unsigned char[_dataSize];
                memcpy(_data, data, _dataSize);
            }*/

            void* RedChannel()
            {
                return _redData;
            }

            void* GreenChannel()
            {
                return _greenData;
            }

            void* BlueChannel()
            {
                return _blueData;
            }

            /*unsigned char* Data()
            {
                return _data;
            }*/

            void SetFormat(ImageFormat format)
            {
                _format = format;
            }

            unsigned int Width() const
            {
                return _width;
            }

            unsigned int Height() const
            {
                return _height;
            }

            ImageFormat Format()
            {
                return _format;
            }

            ImageType Type()
            {
                return _type;
            }

            void SetType(ImageType type)
            {
                _type = type;
            }

            //TODO: Should be called before Set*Channel() at the moment, later (see TODO below) it shouldn't be a problem anymore
            unsigned int DataLength()
            {
                return _dataLength;
            }

            //TODO: Remove memcpy() when static allocator is implemented, just store pointer to data instead
            void SetRedChannel(void* redData)
            {
                _dataLength = _width * _height * (int)_format;

                _redData = new unsigned char[_dataLength];
                memcpy(_redData, redData, _dataLength);
            }

            void SetGreenChannel(void* greenData)
            {
                _greenData = new unsigned char[_dataLength];
                memcpy(_greenData, greenData, _dataLength);
            }

            void SetBlueChannel(void* blueData)
            {
                _blueData = new unsigned char[_dataLength];
                memcpy(_blueData, blueData, _dataLength);
            }
        };
    }
}

#endif //OCIMAGE_H
