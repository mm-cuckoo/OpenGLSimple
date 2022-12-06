package com.sgf.gl

import android.content.Context
import java.io.BufferedReader
import java.io.IOException
import java.io.InputStream
import java.io.InputStreamReader
import java.lang.StringBuilder

object TextResourceReader {
    fun readTextFileFromResource(context: Context, resourceId: Int): String {
        val body = StringBuilder()
        val inputStream: InputStream = context.resources.openRawResource(resourceId)
        val inputStreamReader = InputStreamReader(inputStream)
        val bufferedReader = BufferedReader(inputStreamReader)
        var nextLine: String?
        try {
            while (bufferedReader.readLine().also { nextLine = it } != null) {
                body.append(nextLine)
                body.append('\n')
            }
        } catch (e: IOException) {
            GLog.e("io e==>$e")
        } finally {
            try {
                inputStreamReader.close()
                inputStream.close()
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
        return body.toString()
    }
}