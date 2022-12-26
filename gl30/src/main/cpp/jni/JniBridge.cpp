#include <jni.h>
#include <string>
#include "LogUtils.h"
#include "MyGLRenderContext.h"

#define NATIVE_RENDER_CLASS_NAME "com/sgf/gl30/jni/NativeRender"
#define NATIVE_BG_RENDER_CLASS_NAME "com/sgf/gl30/jni/NativeEglRender"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL native_Test(JNIEnv *env, jobject jobj) {
    std::string str = "get String for cpp openGl 3.0";
    return env->NewStringUTF(str.c_str());
}


JNIEXPORT void JNICALL native_OnInit(JNIEnv *env, jobject jobj) {
    MyGLRenderContext::GetInstance();
}

JNIEXPORT void JNICALL native_OnUnInit(JNIEnv *env , jobject jobj) {
    MyGLRenderContext::DestroyInstance();
}

JNIEXPORT void JNICALL native_OnSurfaceCreated(JNIEnv *env, jobject jobj) {
    MyGLRenderContext::GetInstance()->OnSurfaceCreated();
}

JNIEXPORT void JNICALL native_OnSurfaceChanged(JNIEnv *env, jobject jobj, jint width, jint height) {
    MyGLRenderContext::GetInstance()->OnSurfaceChanged(width, height);
}

JNIEXPORT void JNICALL native_OnDrawFrame(JNIEnv *env, jobject jobj) {
    MyGLRenderContext::GetInstance()->OnDrawFrame();
}

#ifdef __cplusplus
}
#endif

static JNINativeMethod gl_RenderMethods[] = {
        {"native_Test",                 "()Ljava/lang/String;",     (void *) (native_Test)},
        {"native_OnInit",               "()V",                      (void *) (native_OnInit)},
        {"native_OnUnInit",             "()V",                      (void *) (native_OnUnInit)},
        {"native_OnSurfaceCreated",     "()V",                      (void *) (native_OnSurfaceCreated)},
        {"native_OnSurfaceChanged",     "(II)V",                    (void *) (native_OnSurfaceChanged)},
        {"native_OnDrawFrame",          "()V",                      (void *) (native_OnDrawFrame)}
};

static JNINativeMethod gl_BgRenderMethods[] = {
};

static int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods, int methodNum)
{
    LOGCATE("RegisterNativeMethods");
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
    LOGCATE("UnregisterNativeMethods");
    jclass clazz = env->FindClass(className);
    if (clazz == nullptr)
    {
        LOGCATE("UnregisterNativeMethods fail. clazz == NULL");
        return;
    }
    if (env != nullptr)
    {
        env->UnregisterNatives(clazz);
    }
}

// call this func when loading lib
extern "C" jint JNI_OnLoad(JavaVM *jvm, void *p)
{
    LOGCATE("===== JNI_OnLoad =====");
    jint jniRet = JNI_ERR;
    JNIEnv *env = NULL;
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
    JNIEnv *env = NULL;
    if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK)
    {
        return;
    }

    UnregisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME);

    UnregisterNativeMethods(env, NATIVE_BG_RENDER_CLASS_NAME);
}
