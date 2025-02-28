#include "GLUtils.h"
#include <cstdlib>

GLuint GLUtils::LoadShader(GLenum shaderType, const char *pSource)
{
    GLuint shader = 0;
    FUN_BEGIN_TIME("GLUtils::LoadShader")
    shader = glCreateShader(shaderType); // 创建一个着色器， 如果大于0 则成功
    if (shader)
    {
        glShaderSource(shader, 1, &pSource, NULL); // 添加pSource  GL程序代码
        glCompileShader(shader); // 编译GL着色器
        GLint compiledCode = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiledCode); // 获取编译状态code

        // 如果code 不为 0 则表示编译时出现问题， 需要进一步获取编译错误信息
        if (!compiledCode)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);// 获取着色器信息长度
            if (infoLen)
            {
                char *buffer = (char *)malloc((size_t)infoLen); // 开辟空间
                if (buffer)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buffer); // 获取错误信息
                    LOGCATE("GLUtils::LoadShader Could not compile shader %d:\n%s\n", shaderType, buffer);
                    free(buffer); // 释放空间
                }

                glDeleteShader(shader);// 删除编译的着色器
                shader = 0;
            }

        }

    }

    FUN_END_TIME("GLUtils::LoadShader")
    return shader;
}

GLuint GLUtils::CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource,
                              GLuint &vertexShaderHandler, GLuint &fragShaderHandler) {

    GLuint program = 0;

    FUN_BEGIN_TIME("GLUtils::CreateProgram")
        vertexShaderHandler = LoadShader(GL_VERTEX_SHADER, pVertexShaderSource);
        if (!vertexShaderHandler) return program;
        fragShaderHandler = LoadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
        if (!fragShaderHandler) return program;

        program = glCreateProgram();
        LOGCATD("GLUtils::CreateProgram:program code:%d", program);
        if (program) {
            glAttachShader(program, vertexShaderHandler);
            CheckGLError("glAttachShader-v");
            glAttachShader(program, fragShaderHandler);
            CheckGLError("glAttachShader-f");

            glLinkProgram(program);
            GLint linkStatus = GL_FALSE;
            glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

            glDetachShader(program, vertexShaderHandler);
            glDeleteShader(vertexShaderHandler);
            vertexShaderHandler = 0;

            glDetachShader(program, fragShaderHandler);
            glDeleteShader(fragShaderHandler);
            fragShaderHandler = 0;

            if (linkStatus != GL_TRUE) {
                GLint bufLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
                if (bufLength) {
                    char *buf = (char *) malloc((size_t) bufLength);
                    if (buf) {
                        glGetProgramInfoLog(program, bufLength, NULL, buf);
                        LOGCATE("GLUtils::CreateProgram Could not link program:\n%s\n", buf);
                        free(buf);
                    }
                }
                glDeleteProgram(program);
                program = 0;
            }

        }

    FUN_END_TIME("GLUtils::CreateProgram")
    LOGCATE("GLUtils::CreateProgram program = %d", program);
    return program;
}

void GLUtils::CheckGLError(const char *pGLOperation) {

    for (GLint error = glGetError(); error; error = glGetError())
    {
        LOGCATE("GLUtils::CheckGLError GL Operation %s() glError (0x%x)\n", pGLOperation, error);
    }
}
