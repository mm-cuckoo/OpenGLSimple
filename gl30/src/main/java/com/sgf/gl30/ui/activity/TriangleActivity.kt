package com.sgf.gl30.ui.activity

import android.os.Bundle
import com.sgf.gl.TextResourceReader
import com.sgf.gl30.R
import com.sgf.gl30.jni.NativeRender
import com.sgf.gl30.databinding.ActivityGl30TriangleBinding
import com.sgf.gl30.ui.main.BaseActivity

class TriangleActivity : BaseActivity<ActivityGl30TriangleBinding>() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val vShader = TextResourceReader.readTextFileFromResource(this, R.raw.simple_triangle_v_shader)
        val fShader = TextResourceReader.readTextFileFromResource(this, R.raw.simple_triangle_f_shader)
        binding?.myGlSurfaceView?.setRenderType(NativeRender.SAMPLE_TYPE_TRIANGLE, vShader, fShader)
        binding?.myGlSurfaceView?.initRender()

        binding?.btnChangeColor?.setOnClickListener {
            binding?.myGlSurfaceView?.changeColor()
        }
    }

    override fun onDestroy() {
        binding?.myGlSurfaceView?.unInitRender()
        super.onDestroy()
    }

    override fun createRootView(): ActivityGl30TriangleBinding {
        return ActivityGl30TriangleBinding.inflate(layoutInflater)
    }
}