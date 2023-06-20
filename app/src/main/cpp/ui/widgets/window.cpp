#include "window.h"
#include "../factory.h"


bool ui::Window::addChild(SptrWidget&& child) {
    children.emplace_back(child);
    return true;
}

ui::Children* ui::Window::getChildren() {
    return &children;
}

void ui::Window::draw() const {
    if (!visible)
        return;
    for (const auto& child : children)
        child->draw();
}

bool ui::Window::onMouseDown(const MouseEvent& event) {
    if (!screenCoordinates.check(event.x, event.y))
        return false;

    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto& child = *it;
        if (child && child->isVisible() && child->onMouseDown(event))
            return true;
    }

    // TODO : mouse_transparent flag must be here
    return true;
}

bool ui::Window::onMouseUp(const MouseEvent& event) {
    if (!screenCoordinates.check(event.x, event.y))
        return false;

    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto& child = *it;
        if (child && child->isVisible() && child->onMouseUp(event))
            return true;
    }

    // TODO : mouse_transparent flag must be here
    return true;
}

bool ui::Window::onMouseMove(const MouseEvent& event) {
    if (!screenCoordinates.check(event.x, event.y))
        return false;

    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto& child = *it;
        if (child && child->isVisible() && child->onMouseMove(event))
            return true;
    }

    // TODO : mouse_transparent flag must be here
    return true;
}

bool ui::Window::initWidget(const Node& node) {
    if (!this->Widget::initWidget(node))
        return false;

    // Is there nested widgets?
    if (node.HasMember("widgets")) {
        if (!node["widgets"].IsObject())
            return false;
        if (!createNestedWidgets(node["widgets"].GetObject()))
            return false;
    }

    return true;
}

bool ui::Window::createNestedWidgets(const Node& node, bool any /* = true */) {
    const auto &factory = ui::Factory::getInstance();

    for (const auto &obj: node.GetObject()) {
        auto type = getType(obj.value);

        // If not 'any' that windows are only allowed
        if (!any && type != "window")
            return false;

        if (!factory.create(this, type, obj.name.GetString(), obj.value))
            return false;
    }
    return true;
}
