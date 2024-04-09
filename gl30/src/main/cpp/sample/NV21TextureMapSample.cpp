#include "NV21TextureMapSample.h"

NV21TextureMapSample::NV21TextureMapSample(const char *pVShader, const char *pFShader) {
    this->pVShader = pVShader;
    this->pFShader = pFShader;

}

NV21TextureMapSample::~NV21TextureMapSample() {

}

void NV21TextureMapSample::Init() {

}

void NV21TextureMapSample::Draw(int screenW, int screenH) {

}

void NV21TextureMapSample::LoadImage(NativeImage *nativeImage) {
    if (nativeImage) {
        m_RenderImage.format = nativeImage->format;
        m_RenderImage.width = nativeImage->width;
        m_RenderImage.height = nativeImage->height;
        NativeImageUtil::CopyNativeImage(nativeImage, &m_RenderImage);
    }
}

void NV21TextureMapSample::Destroy() {

}

