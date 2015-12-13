#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <chrono>
#include <unordered_map>

#include <inttypes.h>

#include <unistd.h>

#include <memory>

class Variant
{
public:
    Variant() { }

    template<class T>
    Variant(T inValue) :
        mImpl(new VariantImpl<T>(inValue)),
        mClassName(typeid(T).name())
    {
    }

    template<class T>
    T getValue() const
    {
        if (typeid(T).name() != mClassName)
        {
            throw std::logic_error("Non-matching types!");
        }

        return dynamic_cast<VariantImpl<T>*>(mImpl.get())->getValue();
    }

    template<class T>
    void setValue(T inValue)
    {
        mImpl.reset(new VariantImpl<T>(inValue));
        mClassName = typeid(T).name();
    }

private:
    struct AbstractVariantImpl
    {
        virtual ~AbstractVariantImpl() {}
    };

    template<class T>
    struct VariantImpl : public AbstractVariantImpl
    {
        VariantImpl(T inValue) : mValue(inValue) { }

        ~VariantImpl() {}

        T getValue() const { return mValue; }

        T mValue;
    };

    std::shared_ptr<AbstractVariantImpl> mImpl;
    std::string mClassName;
};

enum class SourceFormat
{
    Integer12 = 12,
    Integer14 = 14
};

class Type
{
public:
    virtual ~Type(){}
    virtual void* allocate()const=0;
    virtual void* cast(void* obj)const=0;
};

template<typename T> class TypeImpl : public Type
{
public:
    virtual void* allocate()const{ return new T; }
    virtual void* cast(void* obj)const{ return static_cast<T*>(obj); }
};

template<typename T> class variant
{
    T _value;

public:
    variant(T value)
    {
        _value = value;
    }
};

//variant vTest;

// Source: http://esr.ibiblio.org/?p=5095
static inline uint8_t IsBigEndianMachine()
{
    const uint16_t endianness = 256;
    return *(const uint8_t *)&endianness;
}

inline void SwapEndian(uint16_t &val)
{
    val = (val << 8) |          // left-shift always fills with zeros
            ((uint16_t)val >> 8); // right-shift sign-extends, so force to zero
}

inline void SwapEndian(uint32_t &val)
{
    val = (val<<24) | ((val<<8) & 0x00ff0000) |
            ((val>>8) & 0x0000ff00) | (val>>24);
}

struct TIFFHeader
{
    uint16_t Identifier;
    uint16_t Version;
    uint32_t IFDOffset;
};

uint16_t ifdEntries;

struct TIFFTag
{
    uint16_t ID;
    uint16_t DataType;
    uint32_t DataCount;
    uint32_t DataOffset;
};

void SwapTagEndianess(TIFFTag& tag)
{
    SwapEndian(tag.ID);
    SwapEndian(tag.DataType);
    SwapEndian(tag.DataCount);

    if(tag.DataType == 3)
    {
        SwapEndian((uint16_t&)tag.DataOffset);
    }
    else if(tag.DataType == 4)
    {
        SwapEndian((uint32_t&)tag.DataOffset);
    }
}

// TODO: Test
int main(int argc, char** argv)
{
    //Type* type = new TypeImpl<float>;
    //void* test = type->allocate()->cast(12.345);
    //test = 12.345;
    //        variant<int> vTest2(17.5);

    Variant v(12.345);
    auto a = v.getValue<double>();

    auto start = std::chrono::steady_clock::now();

    bool swapEndianess = false;

    std::ifstream is("Frame000338.dng", std::ifstream::binary);
    if(!is)
    {
        std::cout << "Error: File not found." << std::endl;
        return -1;
    }

    // get length of file:
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);

    //char* buffer2 = new char[length];
    char* buffer = new char[length];

    // std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    is.read(buffer, length);
    // std::cout << "File loaded" << std::endl;

    if(buffer[0] << 8 | buffer[1] == 0x4d4d && !IsBigEndianMachine())
    {
        swapEndianess = true;
    }

    TIFFHeader header;
    memcpy(&header, buffer, sizeof(TIFFHeader));
    SwapEndian(header.Version);
    SwapEndian(header.IFDOffset);

    memcpy(&ifdEntries, buffer + header.IFDOffset, sizeof(ifdEntries));
    SwapEndian(ifdEntries);

    TIFFTag* tags = new TIFFTag[ifdEntries];
    memcpy(tags, buffer + header.IFDOffset + sizeof(ifdEntries), sizeof(TIFFTag) * ifdEntries);

    //int x = 3;
    //std::unordered_map<int, std::function<void()>> vM;
    //vM.insert(std::make_pair(1, [&x] () {x = 12;}));

    //auto it = vM.find(1);
    //it->second();

    unsigned int width;
    unsigned int height;
    SourceFormat bitsPerPixel;
    unsigned char* data = new unsigned char[1];

    std::unordered_map<int, std::function<void(TIFFTag&)>> varMap;
    varMap.insert(std::make_pair(256, [&width] (TIFFTag& tag) { width = tag.DataOffset; }));
    varMap.insert(std::make_pair(257, [&height] (TIFFTag& tag) { height = tag.DataOffset; }));
    varMap.insert(std::make_pair(258, [&bitsPerPixel] (TIFFTag& tag)
    {
        bitsPerPixel = static_cast<SourceFormat>(tag.DataOffset);
    }));
    varMap.insert(std::make_pair(273, [&/*&data, &buffer, &width, &height, &bitsPerPixel*/] (TIFFTag& tag) mutable
    {
        unsigned int size = width * height * ((float)bitsPerPixel / 8);
        data = new unsigned char[size];
        memcpy(data, buffer + tag.DataOffset, size);
    }));

    for(int i = 0; i < ifdEntries; i++)
    {
        SwapTagEndianess(tags[i]);

        std::cout << "Tag ID: " << tags[i].ID << std::endl;

        auto it = varMap.find(tags[i].ID);
        if(it != varMap.end())
        {
            (*it).second(tags[i]);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time: " << timeDiff.count() << "ms" << std::endl;

    delete[] tags;
    delete[] buffer;

    return 0;
}
