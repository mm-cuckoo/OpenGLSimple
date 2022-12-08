package com.sgf.gl20.ui.main

import android.view.ViewGroup
import com.sgf.gl20.databinding.ActivityGl20MainBinding
import com.sgf.gl20.ui.activity.TriangleActivity

class GL20MainActivity : BaseMainActivity<ActivityGl20MainBinding>() {

    override fun getBinding(): ActivityGl20MainBinding {
        return ActivityGl20MainBinding.inflate(layoutInflater)
    }

    override fun getButtonLayout(): ViewGroup {
        return getRootView().btnLayout
    }

    override fun getButtonMap(): Map<String, Class<*>> {
        return mapOf(
            "三角形" to TriangleActivity::class.java
        )
    }
}