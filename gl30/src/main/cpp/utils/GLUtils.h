#ifndef OPENGLSIMPLE_GLUTILS_H
#define OPENGLSIMPLE_GLUTILS_H

#include <GLES3/gl3.h>
#include "LogUtils.h"

class GLUtils {
public:
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
