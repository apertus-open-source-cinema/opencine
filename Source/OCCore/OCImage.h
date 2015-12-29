namespace OC
{
    namespace DataProvider
    {
        enum class ImageFormat
        {
            Integer12,
            Integer16
        };

        class OCImage
        {
            unsigned int _width;
            unsigned int _height;
            unsigned char* _data;
            unsigned int _dataSize;
            ImageFormat _format;

        public:
            void SetWidth(int width)
            {
                _width = width;
            }

            void SetHeight(int height)
            {
                _height = height;
            }

            void SetData(unsigned char* data, unsigned int size)
            {
                _dataSize = size;

                _data = new unsigned char[_dataSize];
                memcpy(_data, data, _dataSize);
            }

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
        };
    }
}
