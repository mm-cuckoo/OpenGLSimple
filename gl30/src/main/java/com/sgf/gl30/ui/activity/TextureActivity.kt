package com.sgf.gl30.ui.activity

import android.graphics.BitmapFactory
import android.os.Bundle
import com.sgf.gl.TextResourceReader
import com.sgf.gl30.R
import com.sgf.gl30.databinding.ActivityGl30TextureBinding
import com.sgf.gl30.jni.NativeRender
import com.sgf.gl30.ui.MyGLSurfaceView.Companion.IMAGE_FORMAT_RGBA
import com.sgf.gl30.ui.main.BaseActivity
import java.nio.ByteBuffer

class TextureActivity : BaseActivity<ActivityGl30TextureBinding>() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val vShader = TextResourceReader.readTextFileFromResource(this, R.raw.simple_texture_v_shader)
        val fShader = TextResourceReader.readTextFileFromResource(this, R.raw.simple_texture_f_shader)
        binding?.myGlSurfaceView?.setRenderType(NativeRender.SAMPLE_TYPE_TEXTURE_MAP, vShader, fShader)
        loadRGBAImage(R.drawable.lye6)
    }

    override fun createRootView(): ActivityGl30TextureBinding {
        return ActivityGl30TextureBinding.inflate(layoutInflater)
    }

    private fun loadRGBAImage(resId : Int) {
        val ins = resources.openRawResource(resId)
        val bitmap = BitmapFactory.decodeStream(ins)
        bitmap?.let {
            val len = it.byteCount
            val buffer = ByteBuffer.allocateDirect(len)
            bitmap.copyPixelsToBuffer(buffer)
            val byteArray = buffer.array()
            binding?.myGlSurfaceView?.setImageData(IMAGE_FORMAT_RGBA, bitmap.width, bitmap.height, byteArray)
        }

    }
}