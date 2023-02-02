package com.sgf.gl30.ui.main

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.viewbinding.ViewBinding

abstract class BaseActivity<B : ViewBinding> : AppCompatActivity() {

    var binding : B ? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = createRootView()
        setContentView(binding!!.root)
    }

    abstract fun createRootView() : B

    override fun onDestroy() {
        super.onDestroy()
        binding = null
    }
}