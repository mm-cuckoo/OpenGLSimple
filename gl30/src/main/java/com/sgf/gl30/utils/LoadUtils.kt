package com.sgf.gl30.utils

import android.content.Context
import java.lang.Exception

object LoadUtils {

    fun loadNV21ImageForAssets(context : Context, path: String) : ByteArray ? {
        try {
            context.assets.open(path).use {
                val length = it.available()
                val buffer = ByteArray(length)
                it.read(buffer)
                return buffer
            }
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return null
    }

}