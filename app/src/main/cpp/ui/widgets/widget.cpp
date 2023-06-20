#include "widget.h"
#include "../../appcore.h"
#include "../../graphics/renderer.h"


ui::Widget::Widget(const Widget* parent, const std::string& name)
    : parent(parent)
    , name(name) {
}

bool ui::Widget::addChild(SptrWidget&& child) {
    return false;
}

ui::Children* ui::Widget::getChildren(){
    return nullptr;
}

bool ui::Widget::onMouseDown(const MouseEvent& event) {
    return screenCoordinates.check(event.x, event.y);
}
bool ui::Widget::onMouseUp(const MouseEvent& event) {
    return screenCoordinates.check(event.x, event.y);
}
bool ui::Widget::onMouseMove(const MouseEvent& event) {
    return screenCoordinates.check(event.x, event.y);
}

bool ui::Widget::onKeyDown(const KeyEvent& event) {
    return false;
}
bool ui::Widget::onKeyUp(const KeyEvent& event) {
    return false;
}

bool ui::Widget::initWidget(const Node& node) {
    if (!readMandatoryAttribute<>(node, "position", position))
        return false;
    if (!readMandatoryAttribute<>(node, "size", size))
        return false;
    if (!readOptionalAttribute<>(node, "visible", visible))
        return false;

    screenCoordinates.leftTop = {0, 0};
    screenCoordinates.rightBottom = size;
    updateScreenCoordinates(screenCoordinates);

    return true;
}

ui::Widget* ui::Widget::findByName(const std::string& widgetName) {
    if (widgetName == name)
        return this;

    Children* children = getChildren();
    if (!children)
        return nullptr;

    for (const auto& child : *children) {
        if (child->findByName(widgetName))
            return child.get();
    }
    return nullptr;
}

std::string ui::Widget::getType(const Node& node) {
    if (node.IsObject() && node.HasMember("type") && node["type"].IsString())
        return std::string(node["type"].GetString());
    else
        return "";
}

std::shared_ptr<Sprite> ui::Widget::createSprite(const ui::Widget::SpriteProperties& properties) {
    Renderer* renderer = AppCore::getInstance().getRenderer();
    auto texture = renderer->getTexture(properties.name);

    auto w = static_cast<float>(texture->getTextureWidth());
    auto h = static_cast<float>(texture->getTextureHeight());
    glm::vec4 relative_uv{
            static_cast<float>(properties.pos.x) / w,
            static_cast<float>(properties.pos.y) / h,
            static_cast<float>(properties.pos.x + properties.size.x) / w,
            static_cast<float>(properties.pos.y + properties.size.y) / h };

    return std::make_shared<Sprite>(screenCoordinates.relative, relative_uv, texture);
}

bool ui::Widget::readSpriteProperties(const Node& node, const char* name,
                                      SpriteProperties& properties) const {
    if (!node.HasMember(name) || !node[name].IsObject())
        return false;

    const auto& obj = node[name].GetObject();

    if (!readMandatoryAttribute<>(obj, "name", properties.name))
        return false;
    if (!readMandatoryAttribute<>(obj, "position", properties.pos))
        return false;
    if (!readMandatoryAttribute<>(obj, "size", properties.size))
        return false;

    return true;
};

void ui::Widget::updateScreenCoordinates(AABB& aabb) const{
    aabb.leftTop += position;
    aabb.rightBottom += position;
    if (parent) {
        parent->updateScreenCoordinates(aabb);
    }
    else {
        // This is desktop than relative coordinates must be calculated
        float w_2 = static_cast<float>(this->size.x) / 2.f;
        float h_2 = static_cast<float>(this->size.y) / 2.f;
        aabb.relative = {
                static_cast<float>(aabb.leftTop.x) / w_2 - 1.f,
                1.f - static_cast<float>(aabb.leftTop.y) / h_2,
                static_cast<float>(aabb.rightBottom.x) / w_2 - 1.f,
                1.f - static_cast<float>(aabb.rightBottom.y) / h_2 };
    }
}
