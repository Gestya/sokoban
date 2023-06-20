#include "factory.h"
#include "widgets/image.h"
#include "widgets/button.h"
#include "widgets/window.h"


ui::Factory::Factory() {
    creators["image"] = [=](const Widget* parent, const std::string& name) {
        return std::make_shared<Image>(parent, name); };
    creators["button"] =  [=](const Widget* parent, const std::string& name) {
        return std::make_shared<Button>(parent, name); };
    creators["window"] =  [=](const Widget* parent, const std::string& name) {
        return std::make_shared<Window>(parent, name); };
}

bool ui::Factory::create(Widget* parent, const std::string& type, const std::string& name, const Node& node) const {
    auto it = creators.find(type);
    if (it == creators.end())
        return false;

    const auto &creator = it->second;
    auto widget = creator(parent, name);
    if (!widget->initWidget(node))
        return false;
    parent->addChild(std::move(widget));

    return true;
}
