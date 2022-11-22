package com.sgf.gl30

class CppGLHandler {
    external fun getStringForJni() : String

    companion object {
        init {
            System.loadLibrary("gl30")
        }
    }
}