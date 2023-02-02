package com.sgf.gl30.ui

import android.opengl.GLSurfaceView
import com.sgf.gl.GLog
import com.sgf.gl30.jni.NativeRender
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRender(private val nativeRender: NativeRender) : GLSurfaceView.Renderer {

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        GLog.d("onSurfaceCreated ==> gl:$gl   config:$config")
        nativeRender.native_OnSurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        GLog.d("onSurfaceChanged ==> gl:$gl  width: $width   height:$height")
        nativeRender.native_OnSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        GLog.d("onDrawFrame gl:$gl")
        nativeRender.native_OnDrawFrame()
    }
}