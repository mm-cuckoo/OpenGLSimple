package com.sgf.gl20.ui.main

import android.view.ViewGroup
import com.sgf.gl20.databinding.ActivityGl20MainBinding
import com.sgf.gl20.ui.activity.cpp.CppTriangleActivity
import com.sgf.gl20.ui.activity.kt.KtTriangleActivity

class GL20MainActivity : BaseMainActivity<ActivityGl20MainBinding>() {

    override fun getBinding(): ActivityGl20MainBinding {
        return ActivityGl20MainBinding.inflate(layoutInflater)
    }

    override fun getKtLayout(): ViewGroup {
        return getRootView().leftLayout
    }

    override fun getCppLayout(): ViewGroup {
        return getRootView().rightLayout
    }

    override fun getKtMap(): Map<String, Class<*>> {
        return mapOf(
            "Kt Triangle" to KtTriangleActivity::class.java,
        )
    }

    override fun getCppMap(): Map<String, Class<*>> {
        return mapOf(
            "Cpp Triangle" to CppTriangleActivity::class.java
        )
    }
}