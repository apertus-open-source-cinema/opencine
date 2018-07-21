// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

__kernel void imageFill(__global unsigned short* channel, const unsigned int width, const unsigned short value)
{
    __local int index;
    index = get_global_id(0) + (get_global_id(1) * width);
    
    channel[index] = value;
}

__kernel void nearestNeighbor(__global unsigned short* channel, const unsigned int width, const int hOffset, const int vOffset, const int colorOffset)
{
    __local int index;
    index = (get_global_id(0) * 2) + ((get_global_id(1) * width * 2)) + colorOffset;
    
    channel[index + hOffset] = channel[index];
    channel[index + vOffset] = channel[index];
    channel[index + hOffset + vOffset] = channel[index];
}
