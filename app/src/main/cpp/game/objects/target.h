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

    const std::string& getTextureName() const override {
        static std::string texture{"target.png"};
        return texture;
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
