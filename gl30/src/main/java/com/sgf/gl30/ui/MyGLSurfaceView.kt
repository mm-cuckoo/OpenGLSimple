package com.sgf.gl30.ui

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import com.sgf.gl.GLog
import com.sgf.gl30.jni.NativeRender

class MyGLSurfaceView : GLSurfaceView {
    
    constructor(context: Context):super(context) {
        init()
    }
    constructor(context: Context, attributeSet: AttributeSet): super(context, attributeSet) {
        init()
    }

    companion object {
        const val IMAGE_FORMAT_RGBA = 0x01
        const val IMAGE_FORMAT_NV21 = 0x02
        const val IMAGE_FORMAT_NV12 = 0x03
        const val IMAGE_FORMAT_I420 = 0x04
        const val IMAGE_FORMAT_YUYV = 0x05
        const val IMAGE_FORMAT_GARY = 0x06
    }

    private val nativeRender = NativeRender()
    private val render = MyGLRender(nativeRender)

    private fun init() {
        // 设置使用GL 的版本
        setEGLContextClientVersion(3)
        setRenderer(render)
        /**
         * 设置使用GL的模式，
         * RENDERMODE_CONTINUOUSLY ：自动调用绘制
         * RENDERMODE_WHEN_DIRTY ： 需要手动触发绘制
         */
        renderMode = RENDERMODE_CONTINUOUSLY // RENDERMODE_WHEN_DIRTY
        GLog.d("init end ===>")
    }

    fun setRenderType(type : Int) {
        nativeRender.native_SetRenderType(type)
    }

    fun setRenderType(type: Int, vShaderStr: String, fShaderStr: String) {
        nativeRender.native_SetRenderTypeAndShader(type, vShaderStr, fShaderStr)
    }

    fun setImageData(format:Int, width: Int, height :Int, imageData: ByteArray) {
        nativeRender.native_SetImageData(format, width, height, imageData)
    }

    fun initRender() {
        nativeRender.native_OnInit()
    }

    fun changeColor() {
        nativeRender.native_OnChangeColor()
    }

    fun unInitRender() {
        nativeRender.native_OnUnInit()
    }

}