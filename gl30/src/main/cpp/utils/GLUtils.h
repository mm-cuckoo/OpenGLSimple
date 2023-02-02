#ifndef OPENGLSIMPLE_GLUTILS_H
#define OPENGLSIMPLE_GLUTILS_H

#include <GLES3/gl3.h>
#include "LogUtils.h"

class GLUtils {
public:
    /**
     * 加载着色器， 在GL 中有两种着色器， 顶点着色器(GL_VERTEX_SHADER)和片源着色器(GL_FRAGMENT_SHADER)
     * @param shaderType : 顶点着色器(GL_VERTEX_SHADER)和片源着色器(GL_FRAGMENT_SHADER)
     * @param pSource : GL 程序
     * @return
     */
    static GLuint LoadShader(GLenum shaderType, const char *pSource);

    static GLuint CreateProgram(
            const char *pVertexShaderSource,
            const char  *pFragShaderSource,
            GLuint &vertexShaderHandler,
            GLuint &fragShaderHandler
            );

    static void CheckGLError(const char *pGLOperation);

};


#endif //OPENGLSIMPLE_GLUTILS_H
