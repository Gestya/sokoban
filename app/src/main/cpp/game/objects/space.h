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

    const std::string& getTextureName() const override {
        static std::string texture{"space.png"};
        return texture;
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
