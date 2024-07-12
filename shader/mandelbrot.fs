#version 330 core
out vec4 FragColor;

in vec2 uv;

uniform float screenRatio;

vec2 cPow(vec2 c) {
    return vec2(c.x*c.x - c.y*c.y, 2.*c.x*c.y);
}

void main() {
    vec2 c = vec2(uv.x * screenRatio, uv.y) - vec2(1.0f, 0.0f);
    vec2 c0 = c;

    for (int i=0; i < 1000; i++) {
        c = cPow(c) + c0;

        if (dot(c,c) > 4) {
            FragColor = vec4(i / 100.0f);
            return;
        }
    }

    FragColor = vec4(1.0f);
} 