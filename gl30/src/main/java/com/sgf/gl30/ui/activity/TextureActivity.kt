package com.sgf.gl30.ui.activity

import android.graphics.BitmapFactory
import android.os.Bundle
import com.sgf.gl30.R
import com.sgf.gl30.databinding.ActivityGl30TextureBinding
import com.sgf.gl30.jni.NativeRender
import com.sgf.gl30.databinding.ActivityGl30TriangleBinding
import com.sgf.gl30.ui.MyGLSurfaceView.Companion.IMAGE_FORMAT_RGBA
import com.sgf.gl30.ui.main.BaseActivity
import java.io.InputStream
import java.nio.ByteBuffer

class TextureActivity : BaseActivity<ActivityGl30TextureBinding>() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding?.myGlSurfaceView?.initRender()
        binding?.myGlSurfaceView?.setRenderType(NativeRender.SAMPLE_TYPE_TEXTURE_MAP)
        loadRGBAImage(R.drawable.lye6)
        binding?.btnChangeColor?.setOnClickListener {
            binding?.myGlSurfaceView?.changeColor()
        }
    }

    override fun onDestroy() {
        binding?.myGlSurfaceView?.unInitRender()
        super.onDestroy()
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