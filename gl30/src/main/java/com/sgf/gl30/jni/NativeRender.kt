package com.sgf.gl30.jni

class NativeRender {
    init {
        System.loadLibrary("gl30")
    }

    external fun native_Test() : String

    external fun native_OnInit()
    external fun native_OnUnInit()
    external fun native_OnChangeColor()
    external fun native_OnSurfaceCreated()
    external fun native_OnSurfaceChanged(width: Int, height: Int)
    external fun native_OnDrawFrame()
}