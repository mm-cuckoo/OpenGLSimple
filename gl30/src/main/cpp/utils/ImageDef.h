//
// Created by machao on 2023/2/21.
//

#ifndef OPENGLSIMPLE_IMAGEDEF_H
#define OPENGLSIMPLE_IMAGEDEF_H

#include <stdint.h>
#include <malloc.h>
#include "LogUtils.h"
#include <string.h>

#define IMAGE_FORMAT_RGBA           0x01
#define IMAGE_FORMAT_NV21           0x02
#define IMAGE_FORMAT_NV12           0x03
#define IMAGE_FORMAT_I420           0x04
#define IMAGE_FORMAT_YUYV           0x05
#define IMAGE_FORMAT_GRAY           0x06
#define IMAGE_FORMAT_I444           0x07
#define IMAGE_FORMAT_P010           0x08

struct NativeImage
{
    int format;
    int width;
    int height;
    uint8_t *ppPlane[3];

    NativeImage() {
        width = 0;
        height = 0;
        format = 0;
        ppPlane[0] = nullptr;
        ppPlane[1] = nullptr;
        ppPlane[2] = nullptr;

    }
};

class NativeImageUtil
{

public:
    static void FreeNativeImage(NativeImage *pImage)
    {
        if (pImage == nullptr || pImage->ppPlane[0] == nullptr) return;

        switch (pImage->format) {
            case IMAGE_FORMAT_RGBA:
                free(pImage->ppPlane[0]);
                break;

            case IMAGE_FORMAT_YUYV:

                break;

            case IMAGE_FORMAT_NV21:
            case IMAGE_FORMAT_NV12:
                break;

            case IMAGE_FORMAT_I420:
                break;
            case IMAGE_FORMAT_GRAY:
                break;
            case IMAGE_FORMAT_I444:
                break;
            case IMAGE_FORMAT_P010:
                break;
            default:
                LOGCATE("FreeNativeImage fail , don`t find image data , format=%d", pImage->format);
                break;
        }

        pImage->ppPlane[0] = nullptr;
        pImage->ppPlane[1] = nullptr;
        pImage->ppPlane[2] = nullptr;
    }

    static void CopyNativeImage(NativeImage *pSrcImg, NativeImage * pDstImg)
    {
        if (pSrcImg == nullptr || pSrcImg->ppPlane[0] == nullptr) return;

        if (pSrcImg->format != pDstImg->format ||
        pSrcImg->height != pDstImg->height ||
            pSrcImg->width != pDstImg->width) return;

        if (pDstImg->ppPlane[0] != nullptr)
        {
            LOGCATD("start free data");
            free(pDstImg->ppPlane[0]);
        }
        LOGCATD("start create new  data");

        MallocNativeImage(pDstImg);

        switch (pSrcImg->format) {
            case IMAGE_FORMAT_RGBA:
                LOGCATD("start copy new  data");
                memcpy(pDstImg->ppPlane[0], pSrcImg->ppPlane[0], pSrcImg->width * pSrcImg->height * 4);
                break;
            default:
                LOGCATE("CopyNativeImage fail , don`t find image copy way , format=%d", pSrcImg->format);
                break;
        }
    }

    static void MallocNativeImage(NativeImage *pImage)
    {
        if (pImage->width == 0 || pImage->height == 0) return;

        switch (pImage->format) {
            case IMAGE_FORMAT_RGBA:
                pImage->ppPlane[0] = (uint8_t *)malloc(pImage->width * pImage->height * 4);
                break;

            case IMAGE_FORMAT_YUYV:

                break;

            case IMAGE_FORMAT_NV21:
            case IMAGE_FORMAT_NV12:
                break;

            case IMAGE_FORMAT_I420:
                break;
            case IMAGE_FORMAT_GRAY:
                break;
            case IMAGE_FORMAT_I444:
                break;
            case IMAGE_FORMAT_P010:
                break;
            default:
                LOGCATE("MallocNativeImage fail , don`t find image format , format=%d", pImage->format);
                break;
        }
    }


};

#endif //OPENGLSIMPLE_IMAGEDEF_H
