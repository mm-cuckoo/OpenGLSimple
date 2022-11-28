package com.sgf.gl20.ui.main

import android.content.Intent
import android.os.Bundle
import android.view.ViewGroup
import android.widget.Button
import androidx.viewbinding.ViewBinding

abstract class BaseMainActivity<T : ViewBinding> : BaseActivity() {
    private lateinit var binding: T

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = getBinding()
        setContentView(binding.root)

        val ktViewGroup = getKtLayout()
        val ktMap = getKtMap()
        ktMap.forEach { (t, u) ->
            val button = Button(this)
            button.setOnClickListener {
                val intent = Intent(this, u)
                startActivity(intent)
            }
            button.text = t
            ktViewGroup.addView(button)
        }
        val cppViewGroup = getCppLayout()
        val cppMap = getCppMap()
        cppMap.forEach { (t, u) ->
            val button = Button(this)
            button.setOnClickListener {
                val intent = Intent(this, u)
                startActivity(intent)
            }
            button.text = t
            cppViewGroup.addView(button)
        }
    }

    fun getRootView() : T {
        return binding
    }

    abstract fun getBinding() : T

    abstract fun getKtLayout() : ViewGroup

    abstract fun getCppLayout() : ViewGroup

    abstract fun getKtMap() : Map<String, Class<*>>

    abstract fun getCppMap() : Map<String, Class<*>>

}