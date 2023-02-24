package com.sgf.gl30.jni

class NativeRender {
    init {
        System.loadLibrary("gl30")
    }

    companion object {
        private const val SAMPLE_TYPE                   = 200
        const val SAMPLE_TYPE_TRIANGLE                  = SAMPLE_TYPE
        const val SAMPLE_TYPE_TEXTURE_MAP               = SAMPLE_TYPE + 1
    }

    external fun native_Test() : String

    external fun native_OnInit()

    external fun native_OnUnInit()

    external fun native_SetRenderType(type : Int)

    external fun native_SetImageData(format : Int, width: Int, height: Int, bytes : ByteArray)

    external fun native_OnChangeColor()

    external fun native_OnSurfaceCreated()

    external fun native_OnSurfaceChanged(width: Int, height: Int)

    external fun native_OnDrawFrame()
}