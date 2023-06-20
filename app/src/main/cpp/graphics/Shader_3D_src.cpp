// TextureVertex shader; it will be loaded from assets in the future
static const char* vertex3d = R"vertex(#version 300 es

in vec3 inPosition;
in vec3 inColor;
out vec3 fragColor;
uniform mat4 uTransform;

void main() {
    fragColor = inColor;
    gl_Position = uTransform * vec4(inPosition, 1.0);
}
)vertex";


// Fragment shader; it will be loaded from assets in the future
static const char* fragment3d = R"fragment(#version 300 es
precision mediump float;

in vec3 fragColor;
out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0);
}
)fragment";