#version 410 core
out vec4 ourColor;
uniform float u_time;

void main() {
    float r = (sin(u_time) + 1.0) / 2.0;
    float g = (cos(u_time * 1.3) + 1.0) / 2.0;
    float b = (sin(u_time * 1.7 + 2.0) + 1.0) / 2.0;
    ourColor = vec4(r, g, b, 0.8);
}