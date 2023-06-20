#include "button.h"
#include "desktop.h"
#include "../../appcore.h"
#include "../../graphics/renderer.h"
#include "../../core/commandmanager.h"


void ui::Button::draw() const {
    if (visible) {
        if (disabled)
            AppCore::getInstance().getRenderer()->draw(disabledSprite);
        else if (pressed)
            AppCore::getInstance().getRenderer()->draw(pressedSprite);
        else
            AppCore::getInstance().getRenderer()->draw(normalSprite);
    }
}

bool ui::Button::onMouseDown(const MouseEvent& event) {
    if (disabled || !screenCoordinates.check(event.x, event.y))
        return false;

    pressed = true;
    Desktop::CapturedWidget = this;
    return true;
}

bool ui::Button::onMouseUp(const MouseEvent& event) {
    if (disabled || !screenCoordinates.check(event.x, event.y))
        return false;

    pressed = false;
    Desktop::CapturedWidget = nullptr;
    if (screenCoordinates.check(event.x, event.y) && command.size())
        AppCore::getInstance().getCommandManager()->invokeCommand(command);
    return true;
}

bool ui::Button::onMouseMove(const MouseEvent& event) {
    if (Desktop::CapturedWidget == this) {
        pressed = screenCoordinates.check(event.x, event.y);
        return true;
    } else
        return screenCoordinates.check(event.x, event.y);
}

bool ui::Button::initWidget(const Node& node) {
    if (!this->Widget::initWidget(node))
        return false;

    if (!readOptionalAttribute<>(node, "command", command))
        return false;

    Widget::SpriteProperties texProp;

    if (!readSpriteProperties(node, "normal", texProp))
        return false;
    normalSprite = createSprite(texProp);

    if (!readSpriteProperties(node, "pressed", texProp))
        return false;
    pressedSprite = createSprite(texProp);

    if (!readSpriteProperties(node, "disabled", texProp))
        return false;
    disabledSprite = createSprite(texProp);

    return true;
}
