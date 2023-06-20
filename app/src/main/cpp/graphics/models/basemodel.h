#ifndef ANDROIDGLINVESTIGATIONS_MODEL_H
#define ANDROIDGLINVESTIGATIONS_MODEL_H

#include "../textureasset.h"
#include "../../glm/glm.hpp"


struct TextureVertex {
    constexpr TextureVertex(const glm::vec3& inPosition, const glm::vec2& inUV)
        : position(inPosition),
          uv(inUV) {}

    glm::vec3 position;
    glm::vec2 uv;
};


typedef uint16_t Index;


class BaseModel {
public:
    inline BaseModel(
            std::vector<TextureVertex> vertices,
            std::vector<Index> indices,
            std::shared_ptr<TextureAsset> texture)
            : vertices_(std::move(vertices)),
              indices_(std::move(indices)),
              texture_(std::move(texture)) {}

    inline TextureVertex* getVertexData() {
        return vertices_.data();
    }

    inline const TextureVertex* getVertexData() const {
        return vertices_.data();
    }

    inline const size_t getIndexCount() const {
        return indices_.size();
    }

    inline const Index* getIndexData() const {
        return indices_.data();
    }

    inline const TextureAsset& getTexture() const {
        return *texture_;
    }

    inline void setTexture(std::shared_ptr<TextureAsset> texture) {
        texture_ = std::move(texture);
    }

protected:
    std::vector<TextureVertex> vertices_;
    std::vector<Index> indices_;
    std::shared_ptr<TextureAsset> texture_;
};


#endif //ANDROIDGLINVESTIGATIONS_MODEL_H