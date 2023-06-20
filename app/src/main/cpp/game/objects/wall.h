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

    std::string getTextureName() override {
        return "wall.png";
    }

    const glm::vec3& getColor() const override {
        static glm::vec3 color = hexToColor(0x1e8742);
        return color;
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
