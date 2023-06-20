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

    std::string getTextureName() override {
        return "dude.png";
    }

    const glm::vec3& getColor() const override {
        static glm::vec3 color = hexToColor(0x871e63);
        return color;
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
