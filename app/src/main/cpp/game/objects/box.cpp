#include "box.h"
#include "../../appcore.h"
#include "../../graphics/renderer.h"

bool game::Box::isHighlighted() const {
    return highlighted;
}

void game::Box::setHighlighted(bool flag) {
    highlighted = flag;
    Renderer* renderer = AppCore::getInstance().getRenderer();
    if (renderer) {
        // 2D version
        //std::string textureName = (highlighted ? "box1.png" : "box0.png");
        //model->setTexture(renderer->getTexture(textureName));
        // 3D version
        model->setColor(getColor());
    }
}
