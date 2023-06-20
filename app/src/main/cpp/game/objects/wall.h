#ifndef SOKOBAN_WALL_H
#define SOKOBAN_WALL_H


#include "object.h"

namespace game {

class Wall : public Object {
public:
    ~Wall() override = default;

    ObjectId getId() override {
        return ObjectId::Wall;
    }

    const std::string& getTextureName() const override {
        static std::string texture{"wall.png"};
        return texture;
    }

    const glm::vec3& getScale() const override {
        static glm::vec3 scale{1.f, 1.f, 1.f};
        return scale;
    }

    const glm::vec3& getTranslate() const override {
        static glm::vec3 translate{0.f, 0.f, -0.5f};
        return translate;
    }
};

} // namespace game

#endif //SOKOBAN_WALL_H
