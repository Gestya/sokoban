#ifndef SOKOBAN_MESH_H
#define SOKOBAN_MESH_H

#include "basemodel.h"


class Mesh : public BaseModel {
public:
    inline Mesh()
           : BaseModel({
                    TextureVertex(glm::vec3{-1.f / 2.0f, -1.f / 2.0f, 1.f / 2.0f},  glm::vec2{0.f, 0.f}),
                    TextureVertex(glm::vec3{1.f / 2.0f, -1.f / 2.0f, 1.f / 2.0f},   glm::vec2{1.f, 0.f}),
                    TextureVertex(glm::vec3{1.f / 2.0f, -1.f / 2.0f, -1.f / 2.0f},  glm::vec2{1.f, 1.f}),
                    TextureVertex(glm::vec3{-1.f / 2.0f, -1.f / 2.0f, -1.f / 2.0f}, glm::vec2{0.f, 1.f}),

                    TextureVertex(glm::vec3{-1.f / 2.0f, 1.f / 2.0f, 1.f / 2.0f},  glm::vec2{0.f, 0.f}),
                    TextureVertex(glm::vec3{1.f / 2.0f, 1.f / 2.0f, 1.f / 2.0f},   glm::vec2{1.f, 0.f}),
                    TextureVertex(glm::vec3{1.f / 2.0f, -1.f / 2.0f, 1.f / 2.0f},  glm::vec2{1.f, 1.f}),
                    TextureVertex(glm::vec3{-1.f / 2.0f, -1.f / 2.0f, 1.f / 2.0f}, glm::vec2{0.f, 1.f}),

                    TextureVertex(glm::vec3{-1.f / 2.0f, 1.f / 2.0f, 1.f / 2.0f},  glm::vec2{0.f, 0.f}),
                    TextureVertex(glm::vec3{-1.f / 2.0f, -1.f / 2.0f, 1.f / 2.0f}, glm::vec2{1.f, 0.f}),
                    TextureVertex(glm::vec3{-1.f / 2.0f, -1.f / 2.0f, -1.f / 2.0f},glm::vec2{1.f, 1.f}),
                    TextureVertex(glm::vec3{-1.f / 2.0f, 1.f / 2.0f, -1.f / 2.0f}, glm::vec2{0.f, 1.f}),

                    TextureVertex(glm::vec3{1.f / 2.0f, -1.f / 2.0f, 1.f / 2.0f},  glm::vec2{0.f, 0.f}),
                    TextureVertex(glm::vec3{1.f / 2.0f, 1.f / 2.0f, 1.f / 2.0f},   glm::vec2{1.f, 0.f}),
                    TextureVertex(glm::vec3{1.f / 2.0f, 1.f / 2.0f, -1.f / 2.0f},  glm::vec2{1.f, 1.f}),
                    TextureVertex(glm::vec3{1.f / 2.0f, -1.f / 2.0f, -1.f / 2.0f}, glm::vec2{0.f, 1.f}),
                  },
                  {0,1,2,2,3,0,  4,5,6,6,7,4,  8,9,10,10,11,8,  12,13,14,14,15,12},
                  nullptr) {}

    inline void setScale(const glm::vec3& inScale);
    inline const glm::vec3& getScale() const;

    inline void setTranslate(const glm::vec3& inTranslate);
    inline glm::vec3 getTranslate() const; // TODO : it should be cont ref!!!

    inline void setPosition(const glm::vec2& inPosition);
    inline const glm::vec2& getPosition() const;

private:
    glm::vec3 scale;
    glm::vec3 translate;

    glm::vec2 position;  // Position on the game field
};


inline void Mesh::setScale(const glm::vec3& inScale) {
    scale = inScale;
}
inline const glm::vec3& Mesh::getScale() const {
    return scale;
}
inline void Mesh::setTranslate(const glm::vec3& inTranslate) {
    translate = inTranslate;
}
inline glm::vec3 Mesh::getTranslate() const {
    return translate + glm::vec3(position.x, -position.y, 0.0f);
}
inline void Mesh::setPosition(const glm::vec2& inPosition) {
    position = inPosition;
}
inline const glm::vec2& Mesh::getPosition() const {
    return position;
}



#endif //SOKOBAN_MESH_H
