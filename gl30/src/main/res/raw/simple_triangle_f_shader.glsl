#version 300 es
precision mediump float;
in vec4 vColor;
out vec4 fragColor;
void main()
{
   fragColor = vColor;
}
/**
 * 第一行表示：着色器的版本，OpenGL ES 2.0版本可以不写。
 * 第二行表示：声明着色器中浮点变量的默认精度。
 * 第三行表示: 声明一个输入名为vColor的4分向量
 * 第四行表示：着色器声明一个输出变量fragColor，这个是一个4分量的向量。
 * 第七行表示：表示将输入的颜色值数据拷贝到fragColor变量中，输出到颜色缓冲区。
 */