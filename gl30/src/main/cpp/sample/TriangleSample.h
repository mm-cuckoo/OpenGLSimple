#ifndef OPENGLSIMPLE_TRIANGLESAMPLE_H
#define OPENGLSIMPLE_TRIANGLESAMPLE_H

#include "GLSampleBase.h"
#include <cstdlib>
#include <string>

class TriangleSample : public GLSampleBase {

public:
    TriangleSample();
    virtual ~TriangleSample();

    virtual void changeColor();
    virtual void Init();
    virtual void Draw(int screenW, int screenH);
    virtual void Destroy();

protected:
    float *mp_colorArray = nullptr;

};


#endif //OPENGLSIMPLE_TRIANGLESAMPLE_H
