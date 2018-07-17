// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

__kernel void imageFill(__global cl_ushort* channel, const cl_uint width, const cl_uint height, const cl_ushort value)
{
    int index;

    index = get_global_id(0);
    
    channel[index] = value;
}
