#ifndef SOKOBAN_TARGET_H
#define SOKOBAN_TARGET_H


#include "object.h"

namespace game {

class Target : public Object {
public:
    ~Target() override = default;

    ObjectId getId() override {
        return ObjectId::Target;
    }

    std::string getTextureName() override {
        return "target.png";
    }

    const glm::vec3& getColor() const override {
        static glm::vec3 color = hexToColor(0xf5f80d);
        return color;
    }

    const glm::vec3& getScale() const override {
        static glm::vec3 scale{0.2f, 0.2f, 0.2f};
        return scale;
    }

    const glm::vec3& getTranslate() const override {
        static glm::vec3 translate{0.f, 0.f, 0.f};
        return translate;
    }
};

} // namespace

#endif //SOKOBAN_TARGET_H
