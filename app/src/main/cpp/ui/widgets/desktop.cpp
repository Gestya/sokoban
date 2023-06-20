#include "desktop.h"


// TODO : this is a right approach but terrible implementation!!!
ui::Widget* ui::Desktop::CapturedWidget{nullptr};


ui::Desktop::Desktop(int width, int height)
    : ui::Window(nullptr, "Desktop") {
    position = {0, 0};
    size = {width, height};
    screenCoordinates.leftTop = position;
    screenCoordinates.leftTop = position + size;
}

bool ui::Desktop::init(const Node& node) {
    return createNestedWidgets(node, false);
}

bool ui::Desktop::onMouseDown(const MouseEvent& event) {
    if (Desktop::CapturedWidget)
        return Desktop::CapturedWidget->onMouseDown(event);

    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto& child = *it;
        if (child && child->isVisible() && child->onMouseDown(event))
            return true;
    }

    return false;
}

bool ui::Desktop::onMouseUp(const MouseEvent& event) {
    if (Desktop::CapturedWidget) {
        bool result = Desktop::CapturedWidget->onMouseUp(event);
        Desktop::CapturedWidget = nullptr;
        return result;
    }

    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto& child = *it;
        if (child && child->isVisible() && child->onMouseUp(event))
            return true;
    }

    return false;
}

bool ui::Desktop::onMouseMove(const MouseEvent& event) {
    if (Desktop::CapturedWidget)
        return Desktop::CapturedWidget->onMouseMove(event);

    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto& child = *it;
        if (child && child->isVisible() && child->onMouseMove(event))
            return true;
    }

    return false;
}
