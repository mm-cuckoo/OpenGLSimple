#version 300 es
precision mediump float;
in vec2 v_texCoord;
layout(location = 0) out vec4 outColor;
uniform sampler2D y_texture;
uniform sampler2D uv_texture;
void main()
{
  vec3 yuv;
  //y_texture 和 uv_texture 分别是 NV21 Y Plane 和 UV Plane 纹理的采样器，对两个纹理采样之后组成一个（y,u,v）三维向量，之后左乘变换矩阵转换为（r,g,b）三维向量。
  yuv.x = texture(y_texture, v_texCoord).r;
  yuv.y = texture(uv_texture, v_texCoord).a - 0.5 ;
  yuv.z = texture(uv_texture, v_texCoord).r - 0.5;

  highp vec3 rgb = mat3(1,1,1, 0,-0.344,1.770, 1.403,  -0.714,0) * yuv;

  outColor = vec4(rgb, 1);
}
/*
上面为什么要减去 0.5
在YUV颜色空间中，Y分量表示亮度（Luma），而U和V分量表示色度（Chroma）。U和V分量的取值范围通常是[-0.5, 0.5]，即它们的中心值是0。这意味着在没有颜色信息的情况下，U和V的值应该是0。
在你的GLSL代码中，yuv.y和yuv.z分别从纹理中读取了U和V分量。由于纹理采样器通常返回的值范围是[0, 1]，而U和V分量的实际范围是[-0.5, 0.5]，因此需要将采样得到的值减去0.5，以将其从[0, 1]的范围转换到[-0.5, 0.5]的范围。
具体来说：
texture(uv_texture, v_texCoord).a 返回的是U分量，范围是[0, 1]，减去0.5后变为[-0.5, 0.5]。
texture(uv_texture, v_texCoord).r 返回的是V分量，范围是[0, 1]，减去0.5后变为[-0.5, 0.5]。
这样做的目的是为了正确地表示YUV颜色空间中的色度信息，以便后续的矩阵乘法能够正确地将YUV颜色空间转换为RGB颜色空间。
总结：减去0.5是为了将U和V分量从[0, 1]的范围转换到[-0.5, 0.5]的范围，以便正确表示YUV颜色空间中的色度信息。
*/