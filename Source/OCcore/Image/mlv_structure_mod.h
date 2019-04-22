/*
 * Copyright (C) 2016 Magic Lantern Team
 *
 * This file is part of Magic Lantern. Whereas Magic Lantern itself
 * is distributed under GPL license, this special header file is meant
 * as a file format specification and thus distributed under a compatible,
 * more flexible license to achieve maximum file format compatibility.
 *
 ***********************************************************************
 *        WARNING: The LGPL license only applies to this one file      *
 ***********************************************************************
 *
 * This header file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This header is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef MLV_STRUCTURE_MOD_H
#define MLV_STRUCTURE_MOD_H

#include <inttypes.h>

/* make sure the structures are packed e.g. using #pragma pack */

struct mlv_hdr_t
{
    // uint8_t     blockType[4];
    uint32_t blockType; // Replaced uint8_t by uint32_t to avoid string comparison of block types
    uint32_t blockSize;
    uint64_t timestamp;
};

struct mlv_file_hdr_t
{
    // uint8_t     fileMagic[4];    /* Magic Lantern Video file header */
    uint32_t fileMagic;
    uint32_t blockSize;       /* size of the whole header */
    uint8_t versionString[8]; /* null-terminated C-string of the exact revision of this format */
    uint64_t fileGuid;        /* UID of the file (group) generated using hw counter, time of day and PRNG */
    uint16_t fileNum;         /* the ID within fileCount this file has (0 to fileCount-1) */
    uint16_t fileCount;       /* how many files belong to this group (splitting or parallel) */
    uint32_t fileFlags;       /* 1=out-of-order data, 2=dropped frames, 4=single image mode, 8=stopped due to error */
    uint16_t videoClass;      /* 0=none, 1=RAW, 2=YUV, 3=JPEG, 4=H.264 */
    uint16_t audioClass;      /* 0=none, 1=WAV */
    uint32_t videoFrameCount; /* number of video frames in this file. set to 0 on start, updated when finished. */
    uint32_t audioFrameCount; /* number of audio frames in this file. set to 0 on start, updated when finished. */
    uint32_t sourceFpsNom;    /* configured fps in 1/s multiplied by sourceFpsDenom */
    uint32_t sourceFpsDenom;  /* denominator for fps. usually set to 1000, but may be 1001 for NTSC */
};

struct mlv_vidf_hdr_t
{
    // uint8_t blockType[4];    /* this block contains one frame of video data */
    // uint32_t blockSize;    /* total frame size */
    // uint64_t timestamp;    /* hardware counter timestamp for this frame (relative to recording start) */
    uint32_t frameNumber; /* unique video frame number */
    uint16_t cropPosX;    /* specifies from which sensor row/col the video frame was copied (8x2 blocks) */
    uint16_t cropPosY;    /* (can be used to process dead/hot pixels) */
    uint16_t panPosX;     /* specifies the panning offset which is cropPos, but with higher resolution (1x1 blocks) */
    uint16_t panPosY;     /* (it's the frame area from sensor the user wants to see) */
    uint32_t frameSpace;  /* size of dummy data before frameData starts, necessary for EDMAC alignment */
    /* uint8_t     frameData[variable]; */
};

typedef struct
{
    uint8_t blockType[4]; /* this block contains audio data */
    uint32_t blockSize;   /* total frame size */
    uint64_t timestamp;   /* hardware counter timestamp for this frame (relative to recording start) */
    uint32_t frameNumber; /* unique audio frame number */
    uint32_t frameSpace;  /* size of dummy data before frameData starts, necessary for EDMAC alignment */
    /* uint8_t     frameData[variable]; */
} mlv_audf_hdr_t;

// TODO: Review the struct, copied over from raw.h of ML source code
struct raw_info
{
    uint32_t api_version;   // increase this when changing the structure
#if INTPTR_MAX == INT32_MAX // only works on 32-bit systems
    void* buffer;           // points to image data
#else
    uint32_t do_not_use_this; // this can't work on 64-bit systems
#endif

    uint32_t height, width, pitch;
    uint32_t frame_size;
    uint32_t bits_per_pixel; // 14

    uint32_t black_level; // autodetected
    uint32_t white_level; // somewhere around 13000 - 16000, varies with camera, settings etc
    // would be best to autodetect it, but we can't do this reliably yet

    // TODO: Check if origin and size can be replaced with jpeg ones
    union // DNG JPEG info
    {
        struct
        {
            uint32_t x, y;          // DNG JPEG top left corner
            uint32_t width, height; // DNG JPEG size
        } jpeg;
        struct
        {
            uint32_t origin[2];
            uint32_t size[2];
        } crop;
    };
    union // DNG active sensor area (Y1, X1, Y2, X2)
    {
        struct
        {
            uint32_t y1, x1, y2, x2;
        } active_area;
        uint32_t dng_active_area[4];
    };
    uint32_t exposure_bias[2]; // DNG Exposure Bias (idk what's that)
    uint32_t cfa_pattern;      // stick to 0x02010100 (RGBG) if you can
    uint32_t calibration_illuminant1;
    int32_t color_matrix1[18]; // DNG Color Matrix
    uint32_t dynamic_range;    // EV x100, from analyzing black level and noise (very close to DxO)
};

struct mlv_rawi_hdr_t
{
    // uint8_t     blockType[4];    /* when videoClass is RAW, this block will contain detailed format information */
    // uint32_t    blockSize;    /* total frame size */
    // uint64_t    timestamp;    /* hardware counter timestamp for this frame (relative to recording start) */
    uint16_t xRes; /* Configured video resolution, may differ from payload resolution */
    uint16_t yRes; /* Configured video resolution, may differ from payload resolution */
    // struct raw_info raw_info;    /* the raw_info structure delivered by raw.c of ML Core */
    raw_info rawInfo;
};

typedef struct
{
    uint8_t blockType[4];    /* when audioClass is WAV, this block contains format details  compatible to RIFF */
    uint32_t blockSize;      /* total frame size */
    uint64_t timestamp;      /* hardware counter timestamp for this frame (relative to recording start) */
    uint16_t format;         /* 1=Integer PCM, 6=alaw, 7=mulaw */
    uint16_t channels;       /* audio channel count: 1=mono, 2=stereo */
    uint32_t samplingRate;   /* audio sampling rate in 1/s */
    uint32_t bytesPerSecond; /* audio data rate */
    uint16_t blockAlign;     /* see RIFF WAV hdr description */
    uint16_t bitsPerSample;  /* audio ADC resolution */
} mlv_wavi_hdr_t;

typedef struct
{
    uint8_t blockType[4];
    uint32_t blockSize;    /* total frame size */
    uint64_t timestamp;    /* hardware counter timestamp for this frame (relative to recording start) */
    uint32_t isoMode;      /* 0=manual, 1=auto */
    uint32_t isoValue;     /* camera delivered ISO value */
    uint32_t isoAnalog;    /* ISO obtained by hardware amplification (most full-stop ISOs, except extreme values) */
    uint32_t digitalGain;  /* digital ISO gain (1024 = 1 EV) - it's not baked in the raw data, so you may want to scale it or
                              adjust the white level */
    uint64_t shutterValue; /* exposure time in microseconds */
} mlv_expo_hdr_t;

typedef struct
{
    uint8_t blockType[4];
    uint32_t blockSize;     /* total frame size */
    uint64_t timestamp;     /* hardware counter timestamp for this frame (relative to recording start) */
    uint16_t focalLength;   /* in mm */
    uint16_t focalDist;     /* in mm (65535 = infinite) */
    uint16_t aperture;      /* f-number * 100 */
    uint8_t stabilizerMode; /* 0=off, 1=on, (is the new L mode relevant) */
    uint8_t autofocusMode;  /* 0=off, 1=on */
    uint32_t flags;         /* 1=CA avail, 2=Vign avail, ... */
    uint32_t lensID;        /* hexadecimal lens ID (delivered by properties?) */
    uint8_t lensName[32];   /* full lens string */
    uint8_t lensSerial[32]; /* full lens serial number */
} mlv_lens_hdr_t;

typedef struct
{
    uint8_t blockType[4];
    uint32_t blockSize; /* total frame size */
    uint64_t timestamp; /* hardware counter timestamp for this frame (relative to recording start) */
    uint16_t tm_sec;    /* seconds (0-59) */
    uint16_t tm_min;    /* minute (0-59) */
    uint16_t tm_hour;   /* hour (0-23) */
    uint16_t tm_mday;   /* day of month (1-31) */
    uint16_t tm_mon;    /* month (0-11) */
    uint16_t tm_year;   /* year since 1900 */
    uint16_t tm_wday;   /* day of week */
    uint16_t tm_yday;   /* day of year */
    uint16_t tm_isdst;  /* daylight saving */
    uint16_t tm_gmtoff; /* GMT offset */
    uint8_t tm_zone[8]; /* time zone string */
} mlv_rtci_hdr_t;

typedef struct
{
    uint8_t blockType[4];
    uint32_t blockSize;       /* total frame size */
    uint64_t timestamp;       /* hardware counter timestamp for this frame (relative to recording start) */
    uint8_t cameraName[32];   /* PROP (0x00000002), offset 0, length 32 */
    uint32_t cameraModel;     /* PROP (0x00000002), offset 32, length 4 */
    uint8_t cameraSerial[32]; /* Camera serial number (if available) */
} mlv_idnt_hdr_t;

typedef struct
{
    uint16_t fileNumber;  /* the logical file number as specified in header */
    uint8_t empty;        /* for future use. set to zero. */
    uint8_t frameType;    /* 1 for VIDF, 2 for AUDF, 0 otherwise */
    uint64_t frameOffset; /* the file offset at which the frame is stored (VIDF/AUDF) */
} mlv_xref_t;

typedef struct
{
    uint8_t blockType[4]; /* can be added in post processing when out of order data is present */
    uint32_t blockSize;   /* this can also be placed in a separate file with only file header plus this block */
    uint64_t timestamp;
    uint32_t frameType;  /* bitmask: 1=video, 2=audio */
    uint32_t entryCount; /* number of xrefs that follow here */
    // mlv_xref_t  xrefEntries;    /* this structure refers to the n'th video/audio frame offset in the files */
} mlv_xref_hdr_t;

typedef struct
{
    uint8_t blockType[4]; /* user definable info string. take number, location, etc. */
    uint32_t blockSize;
    uint64_t timestamp;
    /* uint8_t     stringData[variable]; */
} mlv_info_hdr_t;

typedef struct
{
    uint8_t blockType[4]; /* Dual-ISO information */
    uint32_t blockSize;
    uint64_t timestamp;
    uint32_t dualMode; /* bitmask: 0=off, 1=odd lines, 2=even lines, upper bits may be defined later */
    uint32_t isoValue;
} mlv_diso_hdr_t;

typedef struct
{
    uint8_t blockType[4]; /* markers set by user while recording */
    uint32_t blockSize;
    uint64_t timestamp;
    uint32_t type; /* value may depend on the button being pressed or counts up (t.b.d) */
} mlv_mark_hdr_t;

typedef struct
{
    uint8_t blockType[4];
    uint32_t blockSize;
    uint64_t timestamp;
    uint32_t picStyleId;
    int32_t contrast;
    int32_t sharpness;
    int32_t saturation;
    int32_t colortone;
    uint8_t picStyleName[16];
} mlv_styl_hdr_t;

typedef struct
{
    uint8_t blockType[4]; /* Electronic level (orientation) data */
    uint32_t blockSize;
    uint64_t timestamp;
    uint32_t roll;  /* degrees x100 (here, 45.00 degrees) */
    uint32_t pitch; /* 10.00 degrees */
} mlv_elvl_hdr_t;

typedef struct
{
    uint8_t blockType[4]; /* White balance info */
    uint32_t blockSize;
    uint64_t timestamp;
    uint32_t wb_mode; /* WB_AUTO 0, WB_SUNNY 1, WB_SHADE 8, WB_CLOUDY 2, WB_TUNGSTEN 3, WB_FLUORESCENT 4, WB_FLASH 5, WB_CUSTOM 6,
                         WB_KELVIN 9 */
    uint32_t kelvin;  /* only when wb_mode is WB_KELVIN */
    uint32_t wbgain_r; /* only when wb_mode is WB_CUSTOM */
    uint32_t wbgain_g; /* 1024 = 1.0 */
    uint32_t wbgain_b; /* note: it's 1/canon_gain (uses dcraw convention) */
    uint32_t wbs_gm;   /* WBShift (no idea how to use these in post) */
    uint32_t wbs_ba;   /* range: -9...9 */
} mlv_wbal_hdr_t;

typedef struct
{
    uint8_t blockType[4]; /* DEBG - debug messages for development use, contains no production data */
    uint32_t blockSize;
    uint64_t timestamp;
    uint32_t type;   /* debug data type, for now 0 - text log */
    uint32_t length; /* data can be of arbitrary length and blocks are padded to 32 bits, so store real length */
    /* uint8_t     stringData[variable]; */
} mlv_debg_hdr_t;

#endif // MLV_STRUCTURE_MOD_H
