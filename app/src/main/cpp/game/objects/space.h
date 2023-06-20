#ifndef SOKOBAN_SPACE_H
#define SOKOBAN_SPACE_H


#include "object.h"

namespace game {

class Space : public Object {
public:
    ~Space() override = default;

    ObjectId getId() override {
        return ObjectId::Space;
    }

    std::string getTextureName() override {
        return "space.png";
    }

    const glm::vec3& getColor() const override {
        static glm::vec3 color = hexToColor(0x05192d);
        return color;
    }

    const glm::vec3& getScale() const override {
        static glm::vec3 scale{1.f, 1.f, 0.2f};
        return scale;
    }

    const glm::vec3& getTranslate() const override {
        static glm::vec3 translate{0.f, 0.f, -0.7f};
        return translate;
    }
};

} // namespace

#endif //SOKOBAN_SPACE_H
