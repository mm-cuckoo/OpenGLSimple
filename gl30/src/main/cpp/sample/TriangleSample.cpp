#include "TriangleSample.h"
#include "GLUtils.h"

TriangleSample::TriangleSample() {

}

TriangleSample::~TriangleSample() {

}

void TriangleSample::Init() {

    if (m_ProgramObj != 0) {
        return;
    }

    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vPosition;              \n"
            "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
            "}                                            \n";


    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);

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

//设置三角形顶点坐标
    GLfloat vVertices[] = {
             0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
    };

    if(m_ProgramObj == 0)
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

    // 绘制
    glDrawArrays (GL_TRIANGLES, 0, 3);
    glUseProgram (GL_NONE);
}

void TriangleSample::Destroy() {

    if (m_ProgramObj)
    {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
}
