package com.sgf.gl30.ui.activity

import android.os.Bundle
import com.sgf.gl30.jni.NativeRender
import com.sgf.gl30.databinding.ActivityGl30TriangleBinding
import com.sgf.gl30.ui.main.BaseActivity

class TriangleActivity : BaseActivity() {

    private lateinit var binding: ActivityGl30TriangleBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityGl30TriangleBinding.inflate(layoutInflater)
        setContentView(binding.root)
        val cppGLHandler = NativeRender()
        binding.textNdk.text = cppGLHandler.native_Test()
    }
}