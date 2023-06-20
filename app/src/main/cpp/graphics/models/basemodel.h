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

struct ColorVertex {
    constexpr ColorVertex(const glm::vec3& inPosition, const glm::vec3& inColor)
            : position(inPosition),
              color(inColor) {}

    glm::vec3 position;
    glm::vec3 color;
};

typedef uint16_t Index;


template<class V>
class BaseModel {
public:
    inline BaseModel(
            std::vector<V> vertices,
            std::vector<Index> indices,
            std::shared_ptr<TextureAsset> texture)
            : vertices(std::move(vertices)),
              indices(std::move(indices)),
              texture(std::move(texture)) {}

    inline V* getVertexData() {
        return vertices.data();
    }

    inline const V* getVertexData() const {
        return vertices.data();
    }

    inline const size_t getIndexCount() const {
        return indices.size();
    }

    inline const Index* getIndexData() const {
        return indices.data();
    }

    inline const TextureAsset& getTexture() const {
        return *texture;
    }

protected:
    std::vector<V> vertices;
    std::vector<Index> indices;
    std::shared_ptr<TextureAsset> texture;
};





#endif //ANDROIDGLINVESTIGATIONS_MODEL_H