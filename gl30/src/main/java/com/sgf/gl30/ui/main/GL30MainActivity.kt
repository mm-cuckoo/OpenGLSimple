package com.sgf.gl30.ui.main

import android.view.ViewGroup
import com.sgf.gl30.ui.activity.cpp.CppTriangleActivity
import com.sgf.gl30.ui.activity.kt.KtTriangleActivity
import com.sgf.gl30.databinding.ActivityGl30MainBinding

class GL30MainActivity : BaseMainActivity<ActivityGl30MainBinding>() {

    override fun getBinding(): ActivityGl30MainBinding {
        return ActivityGl30MainBinding.inflate(layoutInflater)
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