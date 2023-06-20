#ifndef SOKOBAN_DUDE_H
#define SOKOBAN_DUDE_H


#include "object.h"

namespace game {

class Dude : public Object {
public:
    ~Dude() override = default;

    ObjectId getId() override {
        return ObjectId::Dude;
    }

    const std::string& getTextureName() const override {
        static std::string texture{"dude.png"};
        return texture;
    }

    const glm::vec3& getScale() const override {
        static glm::vec3 scale{1.f, 1.f, 1.f};
        return scale;
    }

    const glm::vec3& getTranslate() const override {
        static glm::vec3 translate{0.f, 0.f, 0.f};
        return translate;
    }
};

} // namespace game

#endif //SOKOBAN_DUDE_H
