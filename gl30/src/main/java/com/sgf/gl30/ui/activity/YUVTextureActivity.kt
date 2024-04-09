package com.sgf.gl30.ui.activity

import android.os.Bundle
import com.sgf.gl.TextResourceReader
import com.sgf.gl30.R
import com.sgf.gl30.jni.NativeRender
import com.sgf.gl30.databinding.ActivityGl30YuvTextureBinding
import com.sgf.gl30.ui.MyGLSurfaceView.Companion.IMAGE_FORMAT_NV21
import com.sgf.gl30.ui.main.BaseActivity
import com.sgf.gl30.utils.LoadUtils

class YUVTextureActivity : BaseActivity<ActivityGl30YuvTextureBinding>() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val vShader = TextResourceReader.readTextFileFromResource(this, R.raw.simple_yuv_texture_v_shader)
        val fShader = TextResourceReader.readTextFileFromResource(this, R.raw.simple_yuv_texture_f_shader)
        binding?.myGlSurfaceView?.setRenderType(NativeRender.SAMPLE_TYPE_YUV_TEXTURE_MAP, vShader, fShader)
        loadYUVImage("YUV_Image_840x1074.NV21")
    }

    override fun createRootView(): ActivityGl30YuvTextureBinding {
        return ActivityGl30YuvTextureBinding.inflate(layoutInflater)
    }



    private fun loadYUVImage(path : String) {
        LoadUtils.loadNV21ImageForAssets(this, path)?.let {
            binding?.myGlSurfaceView?.setImageData(IMAGE_FORMAT_NV21, 840, 1074,it)
        }
    }
}