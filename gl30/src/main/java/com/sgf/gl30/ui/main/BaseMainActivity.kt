package com.sgf.gl30.ui.main

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.core.view.size
import androidx.viewbinding.ViewBinding

abstract class BaseMainActivity<T : ViewBinding> : BaseActivity<T>() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val buttonGroup = getButtonLayout()
        val buttonMap = getButtonMap()
        buttonMap.forEach { (t, u) ->
            val button = Button(this)
            button.setOnClickListener {
                val intent = Intent(this, u)
                startActivity(intent)
            }
            button.text = t
            addButtonToView(buttonGroup, button)
        }
    }

    open fun addButtonToView(viewGroup : ViewGroup, button : Button) {
        viewGroup.addView(button)
    }

    abstract fun getButtonLayout() : ViewGroup

    abstract fun getButtonMap() : Map<String, Class<*>>



}