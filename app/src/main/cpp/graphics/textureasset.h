#ifndef ANDROIDGLINVESTIGATIONS_TEXTUREASSET_H
#define ANDROIDGLINVESTIGATIONS_TEXTUREASSET_H

#include <memory>
#include <android/asset_manager.h>
#include <GLES3/gl3.h>
#include <string>
#include <vector>

class TextureAsset {
public:
    /*!
     * Loads a texture asset from the assets/ directory
     * @param assetManager Asset manager to use
     * @param assetPath The path to the asset
     * @return a shared pointer to a texture asset, resources will be reclaimed when it's cleaned up
     */
    static std::shared_ptr<TextureAsset>
    loadAsset(AAssetManager *assetManager, const std::string &assetPath);

    ~TextureAsset();

    /*!
     * @return the texture id for use with OpenGL
     */
    constexpr GLuint getTextureID() const { return textureID_; }

    /*!
     * @return the texture width in pixels
     */
    constexpr int32_t getTextureWidth() const { return width_; }

    /*!
     * @return the texture height in pixels
     */
    constexpr int32_t getTextureHeight() const { return height_; }

private:
    inline TextureAsset(GLuint textureId, int32_t width, int32_t height)
        : textureID_(textureId)
        , width_(width)
        , height_(height) {}

    GLuint textureID_;
    int32_t width_;
    int32_t height_;
};

#endif //ANDROIDGLINVESTIGATIONS_TEXTUREASSET_H