// Shader Vertex Code
#sourceToken Vertex
#version 330 core
layout (location=0) in vec3 aPos;

out vec3 vTextCoords;

uniform mat4 uView;
uniform mat4 uProj;

void main()
{
  vTextCoords = aPos;
  //vec4 pos = uProj * uView * vec4(aPos, 1.0);
  //gl_Position = pos.xyww;
  gl_Position = uProj * uView * vec4(aPos, 1.0);
}

// Shader Fragment Code
#sourceToken Fragment
#version 330 core
out vec4 FragColor;

in vec3 vTextCoords;

uniform samplerCube uSkybox;

void main() {

  FragColor = texture(uSkybox, vTextCoords);
}
