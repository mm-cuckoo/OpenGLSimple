#include "TextureMapSample.h"
#include "GLUtils.h"

/**
     char vShaderStr[] =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 a_position;   \n"
            "layout(location = 1) in vec2 a_texCoord;   \n"
            "out vec2 v_texCoord;                       \n"
            "void main()                                \n"
            "{                                          \n"
            "   gl_Position = a_position;               \n"
            "   v_texCoord = a_texCoord;                \n"
            "}                                          \n";

    char fShaderStr[] =
            "#version 300 es                                     \n"
            "precision mediump float;                            \n"
            "in vec2 v_texCoord;                                 \n"
            "layout(location = 0) out vec4 outColor;             \n"
            "uniform sampler2D s_TextureMap;                     \n"
            "void main()                                         \n"
            "{                                                   \n"
            "  outColor = texture(s_TextureMap, v_texCoord);     \n"
            "}                                                   \n";



 */

TextureMapSample::TextureMapSample(const char *pVShader, const char *pFShader) {
    m_TextureId = GL_NONE;
    this->pVShader = pVShader;
    this->pFShader = pFShader;
}

TextureMapSample::~TextureMapSample() {
    NativeImageUtil::FreeNativeImage(&m_RenderImage);
}

void TextureMapSample::Init() {

    // 生成一个纹理，将纹理 id 赋值给 m_TextureId
    glGenTextures(1, &m_TextureId);
    // 将纹理 m_TextureId 绑定到类型 GL_TEXTURE_2D 纹理
    glBindTexture(GL_TEXTURE_2D,m_TextureId);
    //设置纹理 S 轴（横轴）的拉伸方式为截取
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //设置纹理 T 轴（纵轴）的拉伸方式为截取
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //设置纹理采样方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 解除纹理关联
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    m_ProgramObj = GLUtils::CreateProgram(pVShader, pFShader, m_VertexShader, m_FragmentShader);
    if (m_ProgramObj) {
        // 获取片源 s_TextureMap 的句柄
        LOGCATD("gl program create success ");
        m_SamplerLoc = glGetUniformLocation(m_ProgramObj, "s_TextureMap");
    } else {
        LOGCATE("create gl program fail");
    }
}

void TextureMapSample::Draw(int screenW, int screenH) {

    if (m_ProgramObj == GL_NONE || m_TextureId == GL_NONE) return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
/*
 *                Y
 *               |
 * (-1.0f,0.5f)  |    (1.0f,0.5f)
 *    P0 --------|-------- P3
 *     |         |         |
 *     |         |         |
 *     |         |         |
 * -------------------------------- x
 *     |         |         |
 *     |         |         |
 *     |         |         |
 *    P1 --------|-------- P2
 * (-1.0f,-0.5f) |   (1.0f, -0.5f)
 *               |
 * */
    GLfloat verticeCoords[] = {
            -1.0f,  0.5f, 0.0f,  // Position 0
            -1.0f, -0.5f, 0.0f,  // Position 1
            1.0f, -0.5f, 0.0f,  // Position 2
            1.0f,  0.5f, 0.0f,  // Position 3
    };
/*
 *     Y
 *     |
 *     |
 * (0.0f,0.0f)      (1.0f,0.0f)
 * ----P0 --------------- P3 -------- s
 *     |                  |
 *     |                  |
 *     |                  |
 *     |                  |
 *     |                  |
 *     |                  |
 *    P1 ---------------- P2
 * (0.0f,1.0f)    (1.0f, 1.0f)
 *     |
 *     |
 *     T
 * */
    GLfloat textureCoords[] = {
            0.0f,  0.0f,        // TexCoord 0
            0.0f,  1.0f,        // TexCoord 1
            1.0f,  1.0f,        // TexCoord 2
            1.0f,  0.0f         // TexCoord 3
    };

    GLushort indices[] = {0,1,2,
                           0,2,3};

    /**
     * 更新纹理数据
     * 1. 激活纹理单元
     * 2. 绑定纹理id
     * 3. 设置纹理
     * 4. 解除纹理关联
     */
    //激活纹理单元 0
    glActiveTexture(GL_TEXTURE0);
    // 将纹理绑定到纹理单元
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    // 将图片数据设置到纹理上
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_RenderImage.width, m_RenderImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_RenderImage.ppPlane[0]);
    // 解除纹理关联
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    // 使用open gl 程序
    glUseProgram(m_ProgramObj);
    // 设置顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), verticeCoords);
    // 设置纹理坐标
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), textureCoords);

    // 设置顶点参数可用
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
/**
 * 1. 激活纹理单元
 * 2. 绑定纹理id
 * 3. 设置纹理
 * 4. 使用glUniform1i 通知采样器，让其知道它代表的时纹理单元
 */
    //激活纹理单元 0
    glActiveTexture(GL_TEXTURE0);
    // 将纹理绑定到纹理单元
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    // 通知采样器，让其知道它代表的时纹理单元GL_TEXTURE0
    glUniform1i(m_SamplerLoc, GL_NONE);

    glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_SHORT, indices);

}

void TextureMapSample::LoadImage(NativeImage *nativeImage) {
    if (nativeImage) {
        m_RenderImage.width = nativeImage->width;
        m_RenderImage.height = nativeImage->height;
        m_RenderImage.format = nativeImage->format;
        // 将java 传过来的数据进行复制
        LOGCATD("start copy data ====>");
        NativeImageUtil::CopyNativeImage(nativeImage, &m_RenderImage);
    }
}

void TextureMapSample::Destroy() {

    if (m_ProgramObj) {
        glDeleteProgram(m_ProgramObj);
        glDeleteTextures(1, &m_TextureId);
        m_ProgramObj = GL_NONE;
    }
}


