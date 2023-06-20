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

    const std::string& getTextureName() const override {
        static std::string texOff{"box0.png"};
        static std::string texOn{"box1.png"};
        return highlighted ? texOn : texOff;
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
