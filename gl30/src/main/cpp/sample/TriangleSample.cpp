#include "TriangleSample.h"
#include "GLUtils.h"

/**
/**
 * 第一行表示：着色器的版本，OpenGL ES 2.0版本可以不写。
 * 第二行表示：输入一个名为vPosition的4分量向量，layout (location = 0)表示这个变量的位置是顶点属性0。
 * 第三行表示：输入一个名为aColor的4分量向量，layout (location = 1)表示这个变量的位置是顶点属性1。
 * 第四行表示：输出一个名为vColor的4分量向量
 * 第七行表示：将输入数据aColor拷贝到vColor的变量中。
 */
/**
char vShaderStr[] =
      "#version 300 es                          \n"
      "layout(location = 0) in vec4 vPosition;  \n"
      "layout(location = 1) in vec4 aColor;     \n"
      "out vec4 vColor;                         \n"
      "void main()                              \n"
      "{                                        \n"
      "   gl_Position = vPosition;              \n"
      "   vColor = aColor;                      \n"
      "}                                        \n";

*/
 /**
* 第一行表示：着色器的版本，OpenGL ES 2.0版本可以不写。
* 第二行表示：声明着色器中浮点变量的默认精度。
* 第三行表示: 声明一个输入名为vColor的4分向量
* 第四行表示：着色器声明一个输出变量fragColor，这个是一个4分量的向量。
* 第七行表示：表示将输入的颜色值数据拷贝到fragColor变量中，输出到颜色缓冲区。
*/
 /**
char fShaderStr[] =
        "#version 300 es                              \n"
        "precision mediump float;                     \n"
        "in vec4 vColor;                              \n"
        "out vec4 fragColor;                          \n"
        "void main()                                  \n"
        "{                                            \n"
        "   fragColor = vColor;                       \n"
        "}                                            \n";
*/
TriangleSample::TriangleSample(const char *pVShader, const char *pFShader) {
    LOGCATI("vShader: %s", pVShader);
    LOGCATI("fShader: %s", pFShader);
    initColor();
    this->pVShader = pVShader;
    this->pFShader = pFShader;
}

TriangleSample::~TriangleSample() {

}

void TriangleSample::Init() {

    if (m_ProgramObj != 0) {
        return;
    }

    m_ProgramObj = GLUtils::CreateProgram(pVShader, pFShader, m_VertexShader, m_FragmentShader);

}

void TriangleSample::Draw(int screenW, int screenH) {
//    LOGCATE("TriangleSample::Draw");

/*
 *                  Y
 *               |
 *               |
 *               A(0.0f,  0.5f)
 *             / | \
 *            /  |  \
 *           /   |   \
 * -------------------------------- x
 *         /     |     \
 *        /      |      \
 *       B ------|------ C (0.5f, -0.5f)
 * (-0.5f,-0.5f) |
 *               |
 * */

//设置三角形顶点坐标（x, y, z）
    GLfloat vVertices[] = {
             0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
    };

    if(m_ProgramObj == GL_NONE)
        return;
    // 清除buffer
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //重置rgba
    glClearColor(1.0, 1.0, 1.0, 1.0);

    //使用GL程序
    glUseProgram (m_ProgramObj);

    /**
     * 加载顶点数据
     * 1. 顶点数据开始位置
     * 2. 一组数据的长度
     * 3. 顶点描述数据的类型，这里position数组中的数据全部为float，所以是GL_FLOAT
     * 4. 是否需要显卡帮忙把数据归一化到-1到+1区间，这里不需要，所以设置GL_FALSE
     * 5. 一个顶点占有的总的字节数，这里为两个float，所以是sizeof(float)*2
     * 6. 顶点数据
     * */
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
    // 允许顶点着色器读取GPU 的数据
    glEnableVertexAttribArray (0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, mp_colorArray);

    // 绘制
    glDrawArrays (GL_TRIANGLES, 0, 3);

    // 禁止顶点数组句柄
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glUseProgram (GL_NONE);
}

void TriangleSample::Destroy() {

    if (m_ProgramObj)
    {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
    if (mp_colorArray) {
        free(mp_colorArray);
        mp_colorArray = nullptr;
    }

    if (pVShader) {
        delete pVShader;
        pVShader = nullptr;
    }

    if (pFShader) {
        delete pFShader;
        pFShader = nullptr;
    }
}

void TriangleSample::ChangeColor() {
    if (mp_colorArray) {
        float color[] = {
                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f
        };

        memcpy(mp_colorArray, color, sizeof(float) * 12);
    }

}

void TriangleSample::initColor() {
    float color[] = {
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
    };

    auto *colorBuffer = (float *)malloc(sizeof(float) * 12 );
    memcpy(colorBuffer, color, sizeof(float) * 12);
    mp_colorArray = colorBuffer;
}
