//
// Created by machao on 2023/2/22.
//

#ifndef OPENGLSIMPLE_TEXTUREMAPSAMPLE_H
#define OPENGLSIMPLE_TEXTUREMAPSAMPLE_H

#include "GLSampleBase.h"
#include "../utils/ImageDef.h"

class TextureMapSample : public GLSampleBase {
public:
    TextureMapSample();
    virtual ~TextureMapSample();

    virtual void Init();
    virtual void Draw(int screenW, int screenH);
    virtual void LoadImage(NativeImage *nativeImage);
    virtual void Destroy();

protected:
    GLuint m_TextureId = GL_NONE;
    GLint m_SamplerLoc;
    NativeImage m_RenderImage;
};


#endif //OPENGLSIMPLE_TEXTUREMAPSAMPLE_H
