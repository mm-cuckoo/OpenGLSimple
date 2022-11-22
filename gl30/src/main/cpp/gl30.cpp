#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sgf_gl30_CppGLHandler_getStringForJni(JNIEnv *env, jobject thiz) {
    std::string str = "get String for cpp open GL 3.0";
    return env->NewStringUTF(str.c_str());
}