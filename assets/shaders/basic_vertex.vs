#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUvs;
layout (location=2) in vec3 aNorm;
layout (location=3) in vec3 aTang;
layout (location=4) in vec3 aBitang;

out vec3 vPos;

void main() {
  vPos = aBitang;
    //myColor = aColor;
    //gl_Position = vec4(aPos, 1.0);
    gl_Position = vec4(aPos, 1.0);
}
