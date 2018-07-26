// Copyright (c) 2018 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

__kernel void imageFill(__global unsigned short* channel, const unsigned int width, const unsigned short value)
{
    __local int index;
    index = get_global_id(0) + (get_global_id(1) * width);
    
    channel[index] = value;
}

__kernel void nearestBottomRight(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2);

    channel[index + 1] = channel[index];
    channel[index + width] = channel[index];
    channel[index + width + 1] = channel[index];
}

__kernel void nearestBottomLeft(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2) + 1;

    channel[index - 1] = channel[index];
    channel[index + width] = channel[index];
    channel[index + width - 1] = channel[index];
}

__kernel void nearestTopRight(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2) + width;

    channel[index + 1] = channel[index];
    channel[index - width] = channel[index];
    channel[index - width + 1] = channel[index];
}

__kernel void nearestTopLeft(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2) + width + 1;

    channel[index - 1] = channel[index];
    channel[index - width] = channel[index];
    channel[index - width - 1] = channel[index];
}

__kernel void nearestGreen0(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2) + 1;

    channel[index - 1] = channel[index];
    channel[index + width] = channel[index + width - 1];
}

__kernel void nearestGreen1(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2);

    channel[index + 1] = channel[index];
    channel[index + width] = channel[index + width + 1];
}

__kernel void bilinearBottomRight(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2) + width + 1;

    channel[index] = ( channel[index - width - 1] + channel[index - width + 1] + channel[index + width - 1] + channel[index + width + 1] ) >> 2;
    channel[index - 1] = hadd(channel[index + width - 1], channel[index - width - 1]);
    channel[index - width] = hadd(channel[index - width - 1], channel[index - width + 1]);
}

__kernel void bilinearBottomLeft(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2) + width;

    channel[index] = ( channel[index - width - 1] + channel[index - width + 1] + channel[index + width - 1] + channel[index + width + 1] ) >> 2;
    channel[index + 1] = hadd(channel[index + width + 1], channel[index - width + 1]);
    channel[index - width] = hadd(channel[index - width - 1], channel[index - width + 1]);
}

__kernel void bilinearTopRight(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2) + 1;

    channel[index] = ( channel[index - width - 1] + channel[index - width + 1] + channel[index + width - 1] + channel[index + width + 1] ) >> 2;
    channel[index - 1] = hadd(channel[index + width - 1], channel[index - width - 1]);
    channel[index + width] = hadd(channel[index + width - 1], channel[index + width + 1]);
}

__kernel void bilinearTopLeft(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2);

    channel[index] = ( channel[index - width - 1] + channel[index - width + 1] + channel[index + width - 1] + channel[index + width + 1] ) >> 2;
    channel[index + 1] = hadd(channel[index + width + 1], channel[index - width + 1]);
    channel[index + width] = hadd(channel[index + width - 1], channel[index + width + 1]);
}

__kernel void bilinearGreen0(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2);

    channel[index] = ( channel[index - width] + channel[index + width] + channel[index - 1] + channel[index + 1] ) >> 2;

    index += width + 1;

    channel[index] = ( channel[index - width] + channel[index + width] + channel[index - 1] + channel[index + 1] ) >> 2;
}

__kernel void bilinearGreen1(__global unsigned short* channel, const unsigned int width)
{
    __local int index;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2) + 1;

    channel[index] = ( channel[index - width] + channel[index + width] + channel[index - 1] + channel[index + 1] ) >> 2;

    index += width - 1;
    
    channel[index] = ( channel[index - width] + channel[index + width] + channel[index - 1] + channel[index + 1] ) >> 2;
}

__kernel void gediGreen0(__global unsigned short* channel, const unsigned int width)
{
    __local int index, hGrad, vGrad;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2);
    hGrad = abs_diff(channel[index - 1], channel[index + 1]);
    vGrad = abs_diff(channel[index - width], channel[index + width]);

    if (vGrad > hGrad)
    {
	channel[index] = hadd(channel[index - 1], channel[index + 1]);
    }
    else
    {
	channel[index] = hadd(channel[index - width], channel[index + width]);
    }

    index += width + 1;
    hGrad = abs_diff(channel[index - 1], channel[index + 1]);
    vGrad = abs_diff(channel[index - width], channel[index + width]);

    if (vGrad > hGrad)
    {
	channel[index] = hadd(channel[index - 1], channel[index + 1]);
    }
    else
    {
	channel[index] = hadd(channel[index - width], channel[index + width]);
    }
}

__kernel void gediGreen1(__global unsigned short* channel, const unsigned int width)
{
    __local int index, hGrad, vGrad;
    index = (get_global_id(0) * 2) + (get_global_id(1) * width * 2) + 1;
    hGrad = abs_diff(channel[index - 1], channel[index + 1]);
    vGrad = abs_diff(channel[index - width], channel[index + width]);

    if (vGrad > hGrad)
    {
	channel[index] = hadd(channel[index - 1], channel[index + 1]);
    }
    else
    {
	channel[index] = hadd(channel[index - width], channel[index + width]);
    }

    index += width - 1;
    hGrad = abs_diff(channel[index - 1], channel[index + 1]);
    vGrad = abs_diff(channel[index - width], channel[index + width]);

    if (vGrad > hGrad)
    {
	channel[index] = hadd(channel[index - 1], channel[index + 1]);
    }
    else
    {
	channel[index] = hadd(channel[index - width], channel[index + width]);
    }
}


