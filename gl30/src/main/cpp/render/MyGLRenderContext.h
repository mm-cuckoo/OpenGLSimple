#ifndef OPENGLSIMPLE_MYGLRENDERCONTEXT_H
#define OPENGLSIMPLE_MYGLRENDERCONTEXT_H

#include "GLSampleBase.h"
#include "LogUtils.h"
#include "TriangleSample.h"
#include "TextureMapSample.h"
#include "ImageDef.h"

class MyGLRenderContext {

    MyGLRenderContext();

    ~MyGLRenderContext();

public:
    void OnSurfaceCreated();
    void OnSurfaceChanged(int width, int height);
    void OnDrawFrame();
    void OnChangeColor();
    void SetImageData(int format, int width, int height, uint8_t *pData);

    void SetRenderType(int type);
    void SetRenderType(int type, const char *pVShader,const char *pFShader);

    void ReleaseRender();

    static MyGLRenderContext* GetInstance();
    static void DestroyInstance();

private:
    static MyGLRenderContext* sm_pGLContext;
    GLSampleBase * m_pSample = nullptr;
    int m_screenW;
    int m_screenH;

};


#endif //OPENGLSIMPLE_MYGLRENDERCONTEXT_H
