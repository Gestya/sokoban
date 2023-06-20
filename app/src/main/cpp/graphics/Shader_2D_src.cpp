// TextureVertex shader; it will be loaded from assets in the future
static const char* vertex2d = R"vertex(#version 300 es

in vec3 inPosition;
in vec2 inUV;
out vec2 fragUV;
uniform mat4 uTransform;

void main() {
    fragUV = inUV;
    gl_Position = uTransform * vec4(inPosition, 1.0);
}
)vertex";


// Fragment shader; it will be loaded from assets in the future
static const char* fragment2d = R"fragment(#version 300 es
precision mediump float;

in vec2 fragUV;
uniform sampler2D uTexture;
out vec4 outColor;

void main() {
    outColor = texture(uTexture, fragUV);
    outColor.a = 0.9;
}
)fragment";