// Shader Vertex Code
#sourceToken Vertex
#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 uProj;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    Normal = mat3(transpose(inverse(uModel))) * aNormal;
    Position = vec3(uModel * vec4(aPos, 1.0));
    gl_Position = uProj * uView * vec4(Position, 1.0);
}

// Shader Fragment Code
#sourceToken Fragment
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skyBox;

void main()
{
  // Material | Refractive Index
  // Air      -> 1.00
  // Water    -> 1.33
  // Ice      -> 1.309
  // Glass    -> 1.52
  // Diamond  -> 2.42
  //float ratio = 1.00 / 1.309;
  vec3 I = normalize(Position - cameraPos);
  // vec3 R = refract(I, normalize(Normal), ratio); // with ratio
  vec3 R = reflect(I, normalize(Normal));
  FragColor = vec4(texture(skyBox, R).rgb, 1.0);
}
