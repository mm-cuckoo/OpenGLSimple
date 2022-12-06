package com.sgf.gl

import android.opengl.GLES20

object ShaderHelper {
    fun compileVertexShader(shaderCode: String): Int {
        return compileShader(GLES20.GL_VERTEX_SHADER, shaderCode)
    }

    fun compileFragmentShader(shaderCode: String): Int {
        return compileShader(GLES20.GL_FRAGMENT_SHADER, shaderCode)
    }

    private fun compileShader(type: Int, shaderCode: String): Int {

        // 创建一个着色器
        var shaderObjectId = GLES20.glCreateShader(type)
        if (shaderObjectId == 0) {
            GLog.e("create shader fail : type :$type")
        } else {
            // 设置着色器
            GLES20.glShaderSource(shaderObjectId, shaderCode)
            // 编译着色器
            GLES20.glCompileShader(shaderObjectId)
            // 获取编译着色器状态，如果为0 表示编译失败
            val compileStatus = IntArray(1)
            GLES20.glGetShaderiv(shaderObjectId, GLES20.GL_COMPILE_STATUS, compileStatus, 0)
            GLog.i("compile shader status :" + compileStatus[0])
            GLog.i("gl shader info log:" + GLES20.glGetShaderInfoLog(shaderObjectId))
            if (compileStatus[0] == 0) {
                // 如果着色器编译失败，删除创建的着色器
                GLES20.glDeleteShader(shaderObjectId)
                shaderObjectId = 0
            }
        }
        return shaderObjectId
    }

    fun linkProgram(vertexShaderId: Int, fragmentShaderId: Int): Int {
        // 创建应用程序
        var programObjectId = GLES20.glCreateProgram()
        if (programObjectId == 0) {
            GLog.e("create program fail:::$programObjectId")
        } else {
            // 将着色器附到应用程序上
            GLES20.glAttachShader(programObjectId, vertexShaderId)
            GLES20.glAttachShader(programObjectId, fragmentShaderId)

            // 连接着色器
            GLES20.glLinkProgram(programObjectId)
            val linkStatus = IntArray(1)
            GLES20.glGetProgramiv(programObjectId, GLES20.GL_LINK_STATUS, linkStatus, 0)
            GLog.i("link status:" + linkStatus[0])
            GLog.i("link info log:" + GLES20.glGetProgramInfoLog(programObjectId))
            if (linkStatus[0] == 0) {
                GLES20.glDeleteProgram(programObjectId)
                programObjectId = 0
            }
        }
        return programObjectId
    }

    /**
     * 验证OpenGL 对象， 开发中使用，生产要关闭
     * @param programObjectId
     * @return
     */
    fun validateProgram(programObjectId: Int): Boolean {
        GLES20.glValidateProgram(programObjectId)
        val validateStatus = IntArray(1)
        GLES20.glGetProgramiv(programObjectId, GLES20.GL_VALIDATE_STATUS, validateStatus, 0)
        GLog.i("validate status :" + validateStatus[0])
        return validateStatus[0] != 0
    }
}