#ifndef OPENGLSIMPLE_TRIANGLESAMPLE_H
#define OPENGLSIMPLE_TRIANGLESAMPLE_H

#include "GLSampleBase.h"
#include <cstdlib>
#include <string>

class TriangleSample : public GLSampleBase {

public:
    TriangleSample(const char *pVShader, const char *pFShader);
    virtual ~TriangleSample();

    virtual void ChangeColor();
    virtual void Init();
    virtual void Draw(int screenW, int screenH);
    virtual void Destroy();

private:
    void initColor();

protected:
    float *mp_colorArray = nullptr;

};


#endif //OPENGLSIMPLE_TRIANGLESAMPLE_H
