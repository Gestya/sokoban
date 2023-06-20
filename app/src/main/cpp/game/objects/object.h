#ifndef SOKOBAN_OBJECT_H
#define SOKOBAN_OBJECT_H

#include "../../graphics/models/mesh.h"
#include "../../glm/vec2.hpp"

namespace game {

enum class ObjectId {
    Wall = 'W',
    Space = 'S',
    Dude = 'D',
    Box = 'B',
    Target = 'T',
};


class Object {
public:
    Object() {}

    virtual ~Object() {}

    virtual ObjectId getId() = 0;
    virtual const std::string& getTextureName() const = 0;
    virtual const glm::vec3& getScale() const = 0;
    virtual const glm::vec3& getTranslate() const = 0;

    bool isVisible() const;
    void setVisible(bool visibility);

    glm::ivec2& getPosition();
    const glm::ivec2& getPosition() const;
    void setPosition(const glm::ivec2& position);

    Mesh *getModel();
    void setModel(std::shared_ptr<Mesh> model);

protected:
    glm::ivec2 position{-1, -1};
    bool visibility{true};
    std::shared_ptr<Mesh> model;
};


using UptrObject = std::unique_ptr<Object>;

} // namespace game


inline bool game::Object::isVisible() const {
    return visibility;
}
inline void game::Object::setVisible(bool visibility) {
    this->visibility = visibility;
}
inline glm::ivec2& game::Object::getPosition() {
    return position;
}
inline const glm::ivec2& game::Object::getPosition() const {
    return position;
}
inline void game::Object::setPosition(const glm::ivec2& position) {
    this->position = position;
}
inline Mesh* game::Object::getModel() {
    return model.get();
}
inline void game::Object::setModel(std::shared_ptr<Mesh> model) {
    this->model = model;
}



inline glm::vec3 hexToColor(uint32_t hex) {
    uint32_t r = (hex & 0x00FF0000) >> 16;
    uint32_t g = (hex & 0x0000FF00) >> 8;
    uint32_t b = (hex & 0x000000FF);
    return glm::vec3(static_cast<float>(r) / 255.f,
                     static_cast<float>(g) / 255.f,
                     static_cast<float>(b) / 255.f );
}


#endif //SOKOBAN_OBJECT_H
