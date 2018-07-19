// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

__kernel void imageFill(__global unsigned short* channel, const unsigned int width, const unsigned int height, const unsigned short value)
{
    __local int index;

    index = get_global_id(0) + (get_global_id(1) * width);
    
    channel[index] = value;
}
