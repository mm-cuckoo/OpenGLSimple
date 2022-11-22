package com.sgf.gl20

class CppGLHandler {
    external fun getStringForJni() : String

    companion object {
        init {
            System.loadLibrary("gl20")
        }
    }
}