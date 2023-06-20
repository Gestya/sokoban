#ifndef ANDROIDGLINVESTIGATIONS_RENDERER_H
#define ANDROIDGLINVESTIGATIONS_RENDERER_H

#include <EGL/egl.h>
#include <memory>
#include <map>

#include "models/sprite.h"
#include "models/mesh.h"
#include "shader.h"
#include "camera.h"

struct android_app;

class Renderer {
public:
    /*!
     * @param pApp the android_app this Renderer belongs to, needed to configure GL
     */
    inline Renderer(android_app *pApp) :
            app_(pApp),
            display_(EGL_NO_DISPLAY),
            surface_(EGL_NO_SURFACE),
            context_(EGL_NO_CONTEXT),
            width_(0),
            height_(0),
            shaderNeedsNewTransformMatrix_(true) {
        initRenderer();
    }

    virtual ~Renderer();

    /*!
     * Handles input from the android_app.
     *
     * Note: this will clear the input queue
     */
    void handleInput();

    /*!
     * Renders all the models in the renderer
     */
    void render();

    /*!
     * TODO : write comment
     */
    std::shared_ptr<TextureAsset> getTexture(std::string name);

    /*!
     * TODO : write comment
     */
    void draw(std::weak_ptr<Sprite> sprite);

    /*!
     * TODO : write comment
     */
    void addModel3d(std::shared_ptr<Mesh> model);

    /*!
     * TODO : write comment
     */
    void removeModels();

    inline glm::ivec2 getScreenSize() {
        return {width_, height_};
    }

private:
    /*!
     * Performs necessary OpenGL initialization. Customize this if you want to change your EGL
     * context or application-wide settings.
     */
    void initRenderer();

    /*!
     * @brief we have to check every frame to see if the framebuffer has changed in size. If it has,
     * update the viewport accordingly
     */
    void updateRenderArea();

    void draw2d();
    void draw3d();

    android_app *app_ = {nullptr};
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLint width_;
    EGLint height_;
    Camera camera_;

    bool shaderNeedsNewTransformMatrix_;

    std::unique_ptr<Shader> shader_;
    std::vector<std::weak_ptr<Sprite>> sprites_;
    std::vector<std::shared_ptr<Mesh>> models3d_;
    std::map<std::string, std::shared_ptr<TextureAsset>> textures_;

    double time_{0};  // TODO : temporary solution. Approach must be changed
};

#endif //ANDROIDGLINVESTIGATIONS_RENDERER_H