package com.sgf.gl30.jni

class NativeRender {
    init {
        System.loadLibrary("gl30")
    }

    external fun native_Init()
    external fun native_Test() : String
}