#include <jni.h>
#include <string>
#include "LogUtils.h"
#include "MyGLRenderContext.h"

#define NATIVE_RENDER_CLASS_NAME "com/sgf/gl30/jni/NativeRender"
#define NATIVE_BG_RENDER_CLASS_NAME "com/sgf/gl30/jni/NativeEglRender"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL native_Test(JNIEnv *env, jobject instance) {
    std::string str = "get String for cpp openGl 3.0";
    return env->NewStringUTF(str.c_str());
}


JNIEXPORT void JNICALL native_OnInit(JNIEnv *env, jobject instance) {
    MyGLRenderContext::GetInstance();
}

JNIEXPORT void JNICALL native_OnUnInit(JNIEnv *env , jobject instance) {
    MyGLRenderContext::DestroyInstance();
}


JNIEXPORT void JNICALL native_SetRenderType(JNIEnv *env, jobject instance, jint type) {
    MyGLRenderContext::GetInstance()->SetRenderType(type);
}


JNIEXPORT void JNICALL native_SetImageData(JNIEnv *env, jobject instance, jint format,jint width, jint height , jbyteArray imageData) {

    // 获取图像数据长度
    int len = env->GetArrayLength(imageData);
    // 创建一个len 长度的缓冲空间，
    auto *buffer = new uint8_t [len];
    // 将图片内容读取到buffer
    env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte *>(buffer));
    LOGCATD("buffer size:%d, buffer :%s", len, buffer);
    MyGLRenderContext::GetInstance()->SetImageData(format, width, height, buffer);
    // 删除buffer
    delete[] buffer;
    // 释放本地引用
    env->DeleteLocalRef(imageData);

}

JNIEXPORT void JNICALL native_OnChangeColor(JNIEnv *env , jobject instance) {
    MyGLRenderContext::GetInstance()->OnChangeColor();
}

JNIEXPORT void JNICALL native_OnSurfaceCreated(JNIEnv *env, jobject instance) {
    MyGLRenderContext::GetInstance()->OnSurfaceCreated();
}

JNIEXPORT void JNICALL native_OnSurfaceChanged(JNIEnv *env, jobject instance, jint width, jint height) {
    MyGLRenderContext::GetInstance()->OnSurfaceChanged(width, height);
}

JNIEXPORT void JNICALL native_OnDrawFrame(JNIEnv *env, jobject instance) {
    MyGLRenderContext::GetInstance()->OnDrawFrame();
}

#ifdef __cplusplus
}
#endif

static JNINativeMethod gl_RenderMethods[] = {
        {"native_Test",                 "()Ljava/lang/String;",     (void *) (native_Test)},
        {"native_OnInit",               "()V",                      (void *) (native_OnInit)},
        {"native_OnUnInit",             "()V",                      (void *) (native_OnUnInit)},
        {"native_SetRenderType",        "(I)V",                     (void *) (native_SetRenderType)},
        {"native_SetImageData",        "(III[B)V",                  (void *) (native_SetImageData)},
        {"native_OnChangeColor",        "()V",                      (void *) (native_OnChangeColor)},
        {"native_OnSurfaceCreated",     "()V",                      (void *) (native_OnSurfaceCreated)},
        {"native_OnSurfaceChanged",     "(II)V",                    (void *) (native_OnSurfaceChanged)},
        {"native_OnDrawFrame",          "()V",                      (void *) (native_OnDrawFrame)}
};

static JNINativeMethod gl_BgRenderMethods[] = {
};

static int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods, int methodNum)
{
    LOGCATI("RegisterNativeMethods");
    jclass clazz = env->FindClass(className);
    if (clazz == nullptr)
    {
        LOGCATE("RegisterNativeMethods fail. clazz == NULL");
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, methods, methodNum) < 0)
    {
        LOGCATE("RegisterNativeMethods fail");
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static void UnregisterNativeMethods(JNIEnv *env, const char *className)
{
    LOGCATI("UnregisterNativeMethods");
    jclass clazz = env->FindClass(className);
    if (clazz == nullptr)
    {
        LOGCATE("UnregisterNativeMethods fail. clazz == NULL");
        return;
    }
    env->UnregisterNatives(clazz);
}

// call this func when loading lib
extern "C" jint JNI_OnLoad(JavaVM *jvm, void *p)
{
    LOGCATI("===== JNI_OnLoad =====");
    jint jniRet = JNI_ERR;
    JNIEnv *env = nullptr;
    if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK)
    {
        return jniRet;
    }

    jint regRet = RegisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME, gl_RenderMethods,
                                        sizeof(gl_RenderMethods) /
                                        sizeof(gl_RenderMethods[0]));
    if (regRet != JNI_TRUE)
    {
        return JNI_ERR;
    }

    regRet = RegisterNativeMethods(env, NATIVE_BG_RENDER_CLASS_NAME, gl_BgRenderMethods,
                                   sizeof(gl_BgRenderMethods) /
                                   sizeof(gl_BgRenderMethods[0]));
    if (regRet != JNI_TRUE)
    {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}

extern "C" void JNI_OnUnload(JavaVM *jvm, void *p)
{
    JNIEnv *env = nullptr;
    if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK)
    {
        return;
    }

    UnregisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME);

    UnregisterNativeMethods(env, NATIVE_BG_RENDER_CLASS_NAME);
}
