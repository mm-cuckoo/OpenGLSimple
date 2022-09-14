package com.sgf.opengl20

class CppOpenGLHandler {
    external fun getStringForJni() : String

    companion object {
        init {
            System.loadLibrary("opengl20")
        }
    }
}