#include "MyGLRenderContext.h"



MyGLRenderContext * MyGLRenderContext::sm_pGLContext;

MyGLRenderContext::MyGLRenderContext() {
    LOGCATI("MyGLRenderContext");
    this->SetRenderType(SAMPLE_TYPE_KEY_TRIANGLE);
}

MyGLRenderContext::~MyGLRenderContext() {
    LOGCATI("~MyGLRenderContext");
    ReleaseRender();
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
    ReleaseRender();
    switch (type)
    {
        case SAMPLE_TYPE_KEY_TRIANGLE:
            m_pSample = new TriangleSample();
            break;
        case SAMPLE_TYPE_KEY_TEXTURE_MAP:
            m_pSample = new TextureMapSample();
            break;
        default: ;

    }
}

void MyGLRenderContext::OnChangeColor() {
    m_pSample->ChangeColor();
}

void MyGLRenderContext::SetImageData(int format, int width, int height, uint8_t *pData) {

    LOGCATI("GL Render Context : Image Data : format=%d, width=%d, height=%d , pData=%p", format, width, height, pData);
    NativeImage nativeImage;
    nativeImage.format = format;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = pData;
    switch (format) {
        case IMAGE_FORMAT_NV12:
        case IMAGE_FORMAT_NV21:
            // 数组指针偏移
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width *  height;
            break;
        case IMAGE_FORMAT_I420:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
            break;
        default:
            break;
    }

    if (m_pSample) {
        m_pSample->LoadImage(&nativeImage);
    }
}

void MyGLRenderContext::ReleaseRender() {
    LOGCATI("ReleaseRender ===>");
    if (m_pSample) {
        m_pSample->Destroy();
        delete m_pSample;
        m_pSample = nullptr;
    }
}
