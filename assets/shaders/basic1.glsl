// Shader Vertex Code
#sourceToken Vertex
#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUvs;
layout (location=2) in vec3 aNormal;
layout (location=3) in vec3 aTang;
layout (location=4) in vec3 aBitang;
layout (location=5) in vec3 aColor;

out vec3 vColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main() {
    vColor = aColor;
    gl_Position = vec4(uProj * uView * uModel * vec4(aPos, 1.0));
}

// Shader Fragment Code
#sourceToken Fragment
#version 330 core

out vec4 FragColor;
in vec3 vColor;

void main() {
    FragColor = vec4(vColor, 1.0);
}
