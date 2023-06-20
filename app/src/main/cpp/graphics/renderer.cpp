#include "renderer.h"

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <GLES3/gl3.h>
#include <memory>
#include <vector>
#include <android/imagedecoder.h>

#include "../AndroidOut.h"
#include "shader.h"
#include "utility.h"
#include "textureasset.h"

// Shader sources.
// They must be loaded from assets in the future
#include "Shader_SRC.cpp"

#include "../glm/gtc/matrix_transform.hpp"

//#include "../core/timer.h" //  TODO : Debug


//! executes glGetString and outputs the result to logcat
#define PRINT_GL_STRING(s) {aout << #s": "<< glGetString(s) << std::endl;}


/*!
 * @brief if glGetString returns a space separated list of elements, prints each one on a new line
 *
 * This works by creating an istringstream of the input c-style string. Then that is used to create
 * a vector -- each element of the vector is a new element in the input string. Finally a foreach
 * loop consumes this and outputs it to logcat using @a aout
 */
#define PRINT_GL_STRING_AS_LIST(s) { \
std::istringstream extensionStream((const char *) glGetString(s));\
std::vector<std::string> extensionList(\
        std::istream_iterator<std::string>{extensionStream},\
        std::istream_iterator<std::string>());\
aout << #s":\n";\
for (auto& extension: extensionList) {\
    aout << extension << "\n";\
}\
aout << std::endl;\
}


//! Color for cornflower blue. Can be sent directly to glClearColor
#define CORNFLOWER_BLUE 20 / 255.f, 20 / 255.f, 20 / 255.f, 1


Renderer::~Renderer() {
    if (display_ != EGL_NO_DISPLAY) {
        eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context_ != EGL_NO_CONTEXT) {
            eglDestroyContext(display_, context_);
            context_ = EGL_NO_CONTEXT;
        }
        if (surface_ != EGL_NO_SURFACE) {
            eglDestroySurface(display_, surface_);
            surface_ = EGL_NO_SURFACE;
        }
        eglTerminate(display_);
        display_ = EGL_NO_DISPLAY;
    }

    sprites_.clear();
    models3d_.clear();
    textures_.clear();
}

void Renderer::render() {
    // Check to see if the surface has changed size. This is _necessary_ to do every frame when
    // using immersive mode as you'll get no other notification that your renderable area has
    // changed.
    updateRenderArea();

    // setup any other gl related global states
    auto r = static_cast<float>(sin(15 * time_ + 97) * 0.5 + 0.5);
    auto g = static_cast<float>(sin(17 * time_ + 43) * 0.5 + 0.5);
    auto b = static_cast<float>(sin(19 * time_ + 11) * 0.5 + 0.5);
    glClearColor(r/3.0f, g/3.0f, b/3.0f, 1.f);

    // clear color and depth buffers
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    draw3d();
    draw2d();

    // Present the rendered image. This is an implicit glFlush.
    auto swapResult = eglSwapBuffers(display_, surface_);
    assert(swapResult == EGL_TRUE);

    time_ += 0.001;
}

std::shared_ptr<TextureAsset> Renderer::getTexture(std::string name) {
    auto it = textures_.find(name);
    if (it != textures_.end()) {
        return it->second;
    }
    else {
        auto assetManager = app_->activity->assetManager;
        auto texture = TextureAsset::loadAsset(assetManager, name);
        textures_[name] = texture;
        return texture;
    }
}

void Renderer::draw(std::weak_ptr<Sprite> sprite) {
    sprites_.emplace_back(sprite);
}

void Renderer::addModel3d(std::shared_ptr<Mesh> model) {
    models3d_.emplace_back(model);
}

void Renderer::removeModels() {
    sprites_.clear();
    models3d_.clear();
}

void Renderer::initRenderer() {
    // Choose your render attributes
    constexpr EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
    };

    // The default display is probably what you want on Android
    auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    // figure out how many configs there are
    EGLint numConfigs;
    eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);

    // get the list of configurations
    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

    // Find a config we like.
    // Could likely just grab the first if we don't care about anything else in the config.
    // Otherwise hook in your own heuristic
    auto config = *std::find_if(
            supportedConfigs.get(),
            supportedConfigs.get() + numConfigs,
            [&display](const EGLConfig &config) {
                EGLint red, green, blue, depth;
                if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red)
                    && eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green)
                    && eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue)
                    && eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth)) {

                    aout << "Found config with " << red << ", " << green << ", " << blue << ", "
                         << depth << std::endl;
                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }
                return false;
            });

    aout << "Found " << numConfigs << " configs" << std::endl;
    aout << "Chose " << config << std::endl;

    // create the proper window surface
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    EGLSurface surface = eglCreateWindowSurface(display, config, app_->window, nullptr);

    // Create a GLES 3 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext context = eglCreateContext(display, config, nullptr, contextAttribs);

    // get some window metrics
    auto madeCurrent = eglMakeCurrent(display, surface, surface, context);
    assert(madeCurrent);

    display_ = display;
    surface_ = surface;
    context_ = context;

    // make width and height invalid so it gets updated the first frame in @a updateRenderArea()
    width_ = -1;
    height_ = -1;

    PRINT_GL_STRING(GL_VENDOR);
    PRINT_GL_STRING(GL_RENDERER);
    PRINT_GL_STRING(GL_VERSION);
    PRINT_GL_STRING_AS_LIST(GL_EXTENSIONS);

    shader_ = std::unique_ptr<Shader>(
            Shader::loadShader(vertex_shader, fragment_shader, "inPosition", "inUV", "uTransform"));
    assert(shader_);

    // setup any other gl related global states
    glClearColor(CORNFLOWER_BLUE);

    // enable alpha globally for now, you probably don't want to do this in a game
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Must be done once than UI will be able to get a screen size.
    updateRenderArea();
}

void Renderer::updateRenderArea() {
    EGLint width;
    eglQuerySurface(display_, surface_, EGL_WIDTH, &width);

    EGLint height;
    eglQuerySurface(display_, surface_, EGL_HEIGHT, &height);

    if (width != width_ || height != height_) {
        width_ = width;
        height_ = height;
        glViewport(0, 0, width, height);

        camera_.changeAspect(width_, height_);

        // make sure that we lazily recreate the projection matrix before we render
        shaderNeedsNewTransformMatrix_ = true;
    }
}

void Renderer::draw2d() {
    // disable depth testing
    glDisable(GL_DEPTH_TEST);

    shader_->activate();

    shaderNeedsNewTransformMatrix_ = true; // TODO : must be fixed ASAP!!
    if (shaderNeedsNewTransformMatrix_) {
        glm::mat4 identity(1.f);
        shader_->setTransformMatrix(&identity[0][0]);;

        shaderNeedsNewTransformMatrix_ = false;
    }

    for (auto& sprite: sprites_) {
        if (auto s = sprite.lock()) {
            shader_->drawModel(*s);
        }
    }
    sprites_.clear();

    shader_->deactivate();
}

void Renderer::draw3d() {
    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glClearDepthf(1.0f);
    glDepthRangef(0.01f, 1.0f);

    shader_->activate();

    if (shaderNeedsNewTransformMatrix_) {
        // TODO : need to think here!
        // make sure the matrix isn't generated every frame
        shaderNeedsNewTransformMatrix_ = false;
    }

    if (!models3d_.empty()) {
        for (auto& model: models3d_) {
            glm::mat4 translate = glm::translate(glm::mat4(1.0f), model->getTranslate());
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), model->getScale());
            glm::mat4 world = translate * scale;

            glm::mat4 transform = camera_.getProjView() * world;
            shader_->setTransformMatrix(&transform[0][0]);

            shader_->drawModel(*model);
        }
    }

    shader_->deactivate();
}