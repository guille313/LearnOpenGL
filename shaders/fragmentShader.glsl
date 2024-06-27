#version 330 core
out vec4 FragColor;

in vec2 uvCord;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
    FragColor = mix(texture(tex1, uvCord), texture(tex1, uvCord)*0.7, texture(tex2, uvCord).a);
}
