#ifndef SOKOBAN_MESH_H
#define SOKOBAN_MESH_H

#include "basemodel.h"


class Mesh : public BaseModel<ColorVertex> {
public:
    inline Mesh()
            : BaseModel<ColorVertex>({
                    ColorVertex(glm::vec3{-1.f / 2.0f, 1.f / 2.0f, -1.f / 2.0f}, glm::vec3{0.f, 0.f, 0.f}),  // 3
                    ColorVertex(glm::vec3{1.f / 2.0f, 1.f / 2.0f, -1.f / 2.0f}, glm::vec3{0.f, 0.f, 0.f}), // 2
                    ColorVertex(glm::vec3{1.f / 2.0f, -1.f / 2.0f, -1.f / 2.0f}, glm::vec3{0.f, 0.f, 0.f}), // 6
                    ColorVertex(glm::vec3{-1.f / 2.0f, -1.f / 2.0f, -1.f / 2.0f}, glm::vec3{0.f, 0.f, 0.f}), // 7
                    ColorVertex(glm::vec3{-1.f / 2.0f, 1.f / 2.0f, 1.f / 2.0f}, glm::vec3{1.f, 1.f, 1.0}), // 0
                    ColorVertex(glm::vec3{1.f / 2.0f, 1.f / 2.0f, 1.f / 2.0f}, glm::vec3{1.f, 1.f, 1.f}), // 1
                    ColorVertex(glm::vec3{1.f / 2.0f, -1.f / 2.0f, 1.f / 2.0f}, glm::vec3{1.f, 1.f, 1.f}), // 5
                    ColorVertex(glm::vec3{-1.f / 2.0f, -1.f / 2.0f, 1.f / 2.0f}, glm::vec3{1.f, 1.f, 1.f}) // 4
                  },
                                     {0,1,2,  2,3,0,  2,1,5,  5,6,2,  3,2,6,  6,7,3,  0,3,7,  7,4,0,  7,6,5,  5,4,7,  1,0,4,  4,5,1},
                                     nullptr) {}

    inline void setColor(const glm::vec3& inColor);
    inline const glm::vec3& getColor() const;

    inline void setScale(const glm::vec3& inScale);
    inline const glm::vec3& getScale() const;

    inline void setTranslate(const glm::vec3& inTranslate);
    inline glm::vec3 getTranslate() const; // TODO : it shoould be cont ref!!!

    inline void setPosition(const glm::vec2& inPosition);
    inline const glm::vec2& getPosition() const;

private:
    inline void fillGradient();

    glm::vec3 color;
    glm::vec3 scale;
    glm::vec3 translate;

    glm::vec2 position;  // Position on the game field
};


inline void Mesh::setColor(const glm::vec3& inColor) {
    color = inColor;
    fillGradient();
}
inline const glm::vec3& Mesh::getColor() const{
    return color;
}
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


inline void Mesh::fillGradient() {
    static glm::vec3 shiftColor[] {
            {-0.2f, -0.2f, -0.2f},
            {-0.2f, -0.2f, -0.2f},
            {-0.3f, -0.3f, -0.3f},
            {-0.2f, -0.2f, -0.2f},
            {0.15f, 0.15f, 0.15f},
            {0.0f, 0.0f, 0.0f},
            {-0.15f, -0.15f, -0.15f},
            {0.0f, 0.0f, 0.0f},
    };

    ColorVertex* vertex = getVertexData();
    for (int i = 0; i < 8; ++i) {
        vertex->color = color + shiftColor[i];
        // Clamping
        for (int k = 0; k < 3; k++) {
            if (vertex->color[k] > 1.0f)
                vertex->color[k] = 1.0f;
            else if (vertex->color[k] < 0.0f)
                vertex->color[k] = 0.0f;
        }
        vertex++;
    }
}

#endif //SOKOBAN_MESH_H
