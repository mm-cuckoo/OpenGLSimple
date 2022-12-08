package com.sgf.gl30.ui.main

import android.view.ViewGroup
import com.sgf.gl30.ui.activity.TriangleActivity
import com.sgf.gl30.databinding.ActivityGl30MainBinding

class GL30MainActivity : BaseMainActivity<ActivityGl30MainBinding>() {

    override fun getBinding(): ActivityGl30MainBinding {
        return ActivityGl30MainBinding.inflate(layoutInflater)
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