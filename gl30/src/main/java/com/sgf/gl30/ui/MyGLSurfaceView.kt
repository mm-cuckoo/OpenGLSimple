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