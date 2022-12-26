#ifndef OPENGLSIMPLE_GLSAMPLEBASE_H
#define OPENGLSIMPLE_GLSAMPLEBASE_H

#include <GLES3/gl3.h>

#define SAMPLE_TYPE                             200
#define SAMPLE_TYPE_KEY_TRIANGLE                SAMPLE_TYPE + 0
#define SAMPLE_TYPE_KEY_TEXTURE_MAP             SAMPLE_TYPE + 1
#define SAMPLE_TYPE_KEY_YUV_TEXTURE_MAP         SAMPLE_TYPE + 2
class GLSampleBase {

public:
    GLSampleBase()
    {
        m_ProgramObj = 0;
        m_VertexShader = 0;
        m_FragmentShader = 0;

        m_SurfaceWidth = 0;
        m_SurfaceHeight = 0;
    }

    virtual ~GLSampleBase() {

    }


    virtual void Init() = 0;
    virtual void Draw(int screenW, int screenH) = 0;
    virtual void  Destroy() = 0;

protected:
    GLuint m_ProgramObj;
    GLuint m_VertexShader;
    GLuint m_FragmentShader;

    int m_SurfaceWidth;
    int m_SurfaceHeight;
};


#endif //OPENGLSIMPLE_GLSAMPLEBASE_H
