#include "box.h"
#include "../../appcore.h"
#include "../../graphics/renderer.h"

bool game::Box::isHighlighted() const {
    return highlighted;
}

void game::Box::setHighlighted(bool flag) {
    highlighted = flag;
    Renderer* renderer = AppCore::getInstance().getRenderer();
    model->setTexture(renderer->getTexture(getTextureName()));
}
