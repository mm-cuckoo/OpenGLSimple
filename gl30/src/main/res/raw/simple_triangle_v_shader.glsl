#version 300 es
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 aColor;
out vec4 vColor;
void main()
{
   gl_Position = vPosition;
   vColor = aColor;
}
/**
 * 第一行表示：着色器的版本，OpenGL ES 2.0版本可以不写。
 * 第二行表示：输入一个名为vPosition的4分量向量，layout (location = 0)表示这个变量的位置是顶点属性0。
 * 第三行表示：输入一个名为aColor的4分量向量，layout (location = 1)表示这个变量的位置是顶点属性1。
 * 第四行表示：输出一个名为vColor的4分量向量
 * 第七行表示：将输入数据aColor拷贝到vColor的变量中。
 */
