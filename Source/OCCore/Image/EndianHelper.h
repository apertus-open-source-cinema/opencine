#ifndef ENDIANHELPER_H
#define ENDIANHELPER_H

#include <inttypes.h>

inline uint8_t IsBigEndianMachine()
{
    const uint16_t endianness = 256;
    return *reinterpret_cast<const uint8_t *>(&endianness);
}

inline void SwapEndian(uint16_t &val)
{
    val = (val << 8) | // left-shift always fills with zeros
          (static_cast<uint16_t>(val) >> 8); // right-shift sign-extends, so force to zero
}

inline void SwapEndian(uint32_t &val)
{
    val = (val << 24) | ((val << 8) & 0x00ff0000) | ((val >> 8) & 0x0000ff00) | (val >> 24);
}

inline uint16_t GetUInt16(const unsigned char *buf, unsigned int &bufferPosition)
{
    bufferPosition += 2;
    return (static_cast<uint16_t>(buf[0]) << 0) | (static_cast<uint16_t>(buf[1]) << 8);
}

// NOTE: Little endian
inline uint32_t GetUInt32(const unsigned char *buf, unsigned int &bufferPosition)
{
    bufferPosition += 4;

    return (static_cast<uint32_t>(buf[0]) << 0) | (static_cast<uint32_t>(buf[1]) << 8) |
           (static_cast<uint32_t>(buf[2]) << 16) | (static_cast<uint32_t>(buf[3]) << 24);
}

inline uint64_t GetUInt64(const unsigned char *buf, unsigned int &bufferPosition)
{
    bufferPosition += 8;
    return (static_cast<uint64_t>(buf[0]) << 0) | (static_cast<uint64_t>(buf[1]) << 8) |
           (static_cast<uint64_t>(buf[2]) << 16) | (static_cast<uint64_t>(buf[3]) << 24) |
           (static_cast<uint64_t>(buf[4]) << 32) | (static_cast<uint64_t>(buf[5]) << 40) |
           (static_cast<uint64_t>(buf[6]) << 48) | (static_cast<uint64_t>(buf[7]) << 56);
}

#endif //ENDIANHELPER_H
