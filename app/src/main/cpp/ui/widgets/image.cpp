#include "image.h"
#include "../../appcore.h"
#include "../../graphics/renderer.h"


void ui::Image::draw() const {
    if (visible)
        AppCore::getInstance().getRenderer()->draw(sprite);
}

bool ui::Image::initWidget(const Node& node) {
    if (!this->Widget::initWidget(node))
        return false;

    Widget::SpriteProperties texProp;
    if (!readSpriteProperties(node, "sprite", texProp))
        return false;
    sprite = createSprite(texProp);

    return true;
}
