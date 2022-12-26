#ifndef OPENGLSIMPLE_TRIANGLESAMPLE_H
#define OPENGLSIMPLE_TRIANGLESAMPLE_H

#include "GLSampleBase.h"

class TriangleSample : public GLSampleBase {

public:
    TriangleSample();
    virtual ~TriangleSample();

    virtual void Init();
    virtual void Draw(int screenW, int screenH);
    virtual void Destroy();
};


#endif //OPENGLSIMPLE_TRIANGLESAMPLE_H
