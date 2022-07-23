#version 330 core

//in vec3 myColor;
out vec4 FragColor;

in vec3 vPos;

void main() {
    //FragColor = vec4(myColor, 1.0);
    FragColor = vec4(vPos + 0.5 * 0.5, 1.0);
}
