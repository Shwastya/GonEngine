#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUvs;
layout (location=2) in vec3 aNormal;
layout (location=3) in vec3 aTang;
layout (location=4) in vec3 aBitang;

uniform mat4 uProj;
uniform mat4 uView;
uniform mat4 uModel;

out vec2 vUvs;

void main() {

    vUvs = aUvs;
    gl_Position = vec4(uProj * uView * uModel * vec4(aPos, 1.0));
}
