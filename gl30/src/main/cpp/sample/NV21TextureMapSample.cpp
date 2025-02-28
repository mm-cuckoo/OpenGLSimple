#include "NV21TextureMapSample.h"

NV21TextureMapSample::NV21TextureMapSample(const char *pVShader, const char *pFShader) {
    this->pVShader = pVShader;
    this->pFShader = pFShader;

}

NV21TextureMapSample::~NV21TextureMapSample() {

}

void NV21TextureMapSample::Init() {

    m_ProgramObj = GLUtils::CreateProgram(pVShader, pFShader, m_VertexShader, m_FragmentShader);

    if (m_ProgramObj) {
        // 获取Y 分量
        m_yuvYLoc = glGetUniformLocation(m_ProgramObj, "y_texture");
        // 获取UV 分量
        m_yuvUVLoc = glGetUniformLocation(m_ProgramObj, "uv_texture");
        // 创建纹理
        GLuint textureIds[2] = {0};
        glGenTextures(2, textureIds);
        m_ytextureId = textureIds[0];
        m_uvtextureId = textureIds[1];
        LOGCATD("NV21TextureMapSample::Init: textureIds:%s", textureIds);
    } else {
        LOGCATE("NV21TextureMapSample create Program Fail");
    }

}

void NV21TextureMapSample::Draw(int screenW, int screenH) {
    if (m_ProgramObj == GL_NONE || m_ytextureId == GL_NONE || m_uvtextureId == GL_NONE) {
        return;
    }
    // 更新y 平面分量
    glBindTexture(GL_TEXTURE_2D, m_ytextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_RenderImage.width, m_RenderImage.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_RenderImage.ppPlane[0]);
    //设置纹理 S 轴（横轴）的拉伸方式为截取
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //设置纹理 T 轴（纵轴）的拉伸方式为截取
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //设置纹理采样方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 解除纹理关联
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    // 更新y 平面分量
    glBindTexture(GL_TEXTURE_2D, m_uvtextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_RenderImage.width >>  1, m_RenderImage.height >> 1 , 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_RenderImage.ppPlane[0]);
    //设置纹理 S 轴（横轴）的拉伸方式为截取
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //设置纹理 T 轴（纵轴）的拉伸方式为截取
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //设置纹理采样方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 解除纹理关联
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    GLfloat verticesCoords[] = {
            -1.0f,  0.78f, 0.0f,  // Position 0
            -1.0f, -0.78f, 0.0f,  // Position 1
            1.0f,  -0.78f, 0.0f,  // Position 2
            1.0f,   0.78f, 0.0f,  // Position 3
    };

    GLfloat textureCoords[] = {
            0.0f,  0.0f,        // TexCoord 0
            0.0f,  1.0f,        // TexCoord 1
            1.0f,  1.0f,        // TexCoord 2
            1.0f,  0.0f         // TexCoord 3
    };

    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    glUseProgram(m_ProgramObj);

    // GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), verticesCoords);
    /**
     * index = 1：表示这个属性数据将绑定到顶点着色器中位置索引为 1 的属性。 =》 layout(location = 1) in vec2 texCoord;
     * 2：表示每个纹理坐标由 2 个分量组成（s 和 t，即纹理坐标的 U 和 V）。
     * GL_FLOAT：表示纹理坐标的数据类型是浮点数。
     * GL_FALSE：表示不需要对数据进行归一化。
     * 2 * sizeof(GLfloat)：表示纹理坐标数据之间的步长（stride），即每个纹理坐标占用的字节数。这里每个纹理坐标有 2 个浮点数，所以步长是 2 * sizeof(GLfloat)。
     * textureCoords：是纹理坐标数据的指针。
     */
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), textureCoords);
    // 启用指定索引的顶点属性数组
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_ytextureId);

    // 用于将整数值传递给着色器程序中的 uniform 变量。Uniform 变量是着色器程序中一种特殊的全局变量，它们的值在绘制过程中是常量（即不会随顶点或片段变化），但可以在 CPU 端通过 OpenGL API 动态设置。
    glUniform1i(m_yuvYLoc, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_uvtextureId);

    glUniform1i(m_yuvUVLoc, 1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

}

void NV21TextureMapSample::LoadImage(NativeImage *nativeImage) {
    if (nativeImage) {
        m_RenderImage.format = nativeImage->format;
        m_RenderImage.width = nativeImage->width;
        m_RenderImage.height = nativeImage->height;
        NativeImageUtil::CopyNativeImage(nativeImage, &m_RenderImage);
    }
}

void NV21TextureMapSample::Destroy() {

}

