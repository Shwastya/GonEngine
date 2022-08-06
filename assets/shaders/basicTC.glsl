// Shader Vertex Code
#sourceToken Vertex
#version 330 core

uniform int uTextScale;

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

    vUvs = aUvs * uTextScale;
    gl_Position = vec4(uProj * uView * uModel * vec4(aPos, 1.0));
}

// Shader Fragment Code
#sourceToken Fragment
#version 330 core
uniform vec4 uColorMask;


out vec4 FragColor;
in vec2 vUvs;
uniform sampler2D uTexture;

void main() {
  FragColor = texture(uTexture, vUvs) * uColorMask;
}
