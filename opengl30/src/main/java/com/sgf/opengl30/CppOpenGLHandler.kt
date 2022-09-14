package com.sgf.opengl30

class CppOpenGLHandler {
    external fun getStringForJni() : String

    companion object {
        init {
            System.loadLibrary("opengl30")
        }
    }
}