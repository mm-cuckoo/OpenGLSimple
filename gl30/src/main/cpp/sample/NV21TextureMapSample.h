//
// Created by machao on 2023-06-07.
//

#ifndef OPENGLSIMPLE_NV21TEXTUREMAPSAMPLE_H
#define OPENGLSIMPLE_NV21TEXTUREMAPSAMPLE_H

#include "GLSampleBase.h"
#include "GLUtils.h"

class NV21TextureMapSample : public GLSampleBase {
public:
    NV21TextureMapSample(const char *pVShader, const char *pFShader);
    virtual ~NV21TextureMapSample();

    virtual void Init();
    virtual void Draw(int screenW, int screenH);
    virtual void LoadImage(NativeImage *nativeImage);
    virtual void Destroy();

protected:
    NativeImage m_RenderImage;
    GLuint m_yuvYLoc;
    GLuint m_yuvUVLoc;
    GLuint m_ytextureId;
    GLuint m_uvtextureId;
};


#endif //OPENGLSIMPLE_NV21TEXTUREMAPSAMPLE_H
