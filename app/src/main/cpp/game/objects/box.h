#ifndef SOKOBAN_BOX_H
#define SOKOBAN_BOX_H


#include "object.h"

namespace game {

class Box : public Object {
public:
    ~Box() override = default;

    ObjectId getId() override {
        return ObjectId::Box;
    }

    std::string getTextureName() override {
        // TODO : must use both textures or use advanced shader or ...
        return "box0.png";
    }

    const glm::vec3& getColor() const override {
        static glm::vec3 colorOn = hexToColor(0xde5a15);
        static glm::vec3 colorOff = hexToColor(0xca7346);
        return highlighted ? colorOn : colorOff;
    }

    const glm::vec3& getScale() const override {
        static glm::vec3 scale{1.f, 1.f, 1.f};
        return scale;
    }

    const glm::vec3& getTranslate() const override {
        static glm::vec3 translate{0.f, 0.f, 0.f};
        return translate;
    }

    bool isHighlighted() const;
    void setHighlighted(bool flag);

private:
    bool highlighted{false};
};

} // namespace game

#endif //SOKOBAN_BOX_H
