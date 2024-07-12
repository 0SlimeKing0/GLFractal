#version 330 core
out vec4 FragColor;

in vec2 uv;

uniform float screenRatio;

void main()
{
    FragColor = vec4(uv, 0.0f, 1.0f);
} 