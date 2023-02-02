#ifndef OPENGLSIMPLE_MYGLRENDERCONTEXT_H
#define OPENGLSIMPLE_MYGLRENDERCONTEXT_H

#include "GLSampleBase.h"
#include "LogUtils.h"
#include "TriangleSample.h"

class MyGLRenderContext {

    MyGLRenderContext();

    ~MyGLRenderContext();

public:
    void OnSurfaceCreated();
    void OnSurfaceChanged(int width, int height);
    void OnDrawFrame();
    void OnChangeColor();

    void SetRenderType(int type);

    static MyGLRenderContext* GetInstance();
    static void DestroyInstance();

private:
    static MyGLRenderContext* sm_pGLContext;
    GLSampleBase * m_pSample;
    int m_screenW;
    int m_screenH;

};


#endif //OPENGLSIMPLE_MYGLRENDERCONTEXT_H
