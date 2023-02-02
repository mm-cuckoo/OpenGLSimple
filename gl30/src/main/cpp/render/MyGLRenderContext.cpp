#include "MyGLRenderContext.h"



MyGLRenderContext * MyGLRenderContext::sm_pGLContext;

MyGLRenderContext::MyGLRenderContext() {
    LOGCATI("MyGLRenderContext");
    this->SetRenderType(SAMPLE_TYPE_KEY_TRIANGLE);
}

MyGLRenderContext::~MyGLRenderContext() {
    LOGCATI("~MyGLRenderContext");
    if (m_pSample) {
        m_pSample->Destroy();
        delete m_pSample;
        m_pSample = nullptr;
    }
}

void MyGLRenderContext::OnSurfaceCreated() {
    LOGCATI("MyGLRenderContext::OnSurfaceCreated");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_pSample->Init();

}

void MyGLRenderContext::OnSurfaceChanged(int width, int height) {
    LOGCATI("OnSurfaceChanged ==> width:%d, height:%d", width, height);
    glViewport(0,0, width, height);
    m_screenW = width;
    m_screenH = height;
}

void MyGLRenderContext::OnDrawFrame() {
    m_pSample->Draw(m_screenW, m_screenH);
//    LOGCATI("OnDrawFrame");

}

MyGLRenderContext *MyGLRenderContext::GetInstance() {
    if (sm_pGLContext == nullptr) {
        LOGCATI("create render context");
        sm_pGLContext = new MyGLRenderContext();
    }

    return sm_pGLContext;
}

void MyGLRenderContext::DestroyInstance() {
    if (sm_pGLContext) {
        LOGCATI("release render context");
        delete sm_pGLContext;
        sm_pGLContext = nullptr;
    }
}

void MyGLRenderContext::SetRenderType(int type) {
    switch (type)
    {
        case SAMPLE_TYPE_KEY_TRIANGLE:
            m_pSample = new TriangleSample();
            break;
        default: ;

    }
}

void MyGLRenderContext::OnChangeColor() {
    m_pSample->changeColor();
}
