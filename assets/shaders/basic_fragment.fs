#version 330 core

//in vec3 myColor;
out vec4 FragColor;

in vec3 vColor;

void main() {
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = vec4(vColor, 1.0);
}
