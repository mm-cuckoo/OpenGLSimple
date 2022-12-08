package com.sgf.gl20.ui.activity

import android.os.Bundle
import com.sgf.gl20.databinding.ActivityGl20TriangleBinding
import com.sgf.gl20.ui.main.BaseActivity

class TriangleActivity : BaseActivity() {

    private lateinit var binding: ActivityGl20TriangleBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityGl20TriangleBinding.inflate(layoutInflater)
        setContentView(binding.root)
    }
}