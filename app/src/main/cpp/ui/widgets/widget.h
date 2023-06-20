#ifndef SOKOBAN_WIDGET_H
#define SOKOBAN_WIDGET_H

#include "../../graphics/models/sprite.h"
#include "../../core/eventlistener.h"
#include "../../rapidjson/document.h"
#include <memory>
#include <string>
#include <set>


namespace ui {

class Widget;
using SptrWidget = std::shared_ptr<Widget>;
using Children = std::vector<SptrWidget>;
using Node = rapidjson::Value;


class Widget {
public:
    Widget(const Widget* parent, const std::string& name);
    virtual ~Widget() = default;

    virtual bool addChild(SptrWidget&& child);
    virtual Children* getChildren();

    virtual bool onMouseDown(const MouseEvent& event);
    virtual bool onMouseUp(const MouseEvent& event);
    virtual bool onMouseMove(const MouseEvent& event);
    virtual bool onKeyDown(const KeyEvent& event);
    virtual bool onKeyUp(const KeyEvent& event);

    virtual bool initWidget(const Node& node);

    virtual void draw() const = 0;

    Widget* findByName(const std::string& widgetName);

    // Properties
    inline const std::string getName() const;
    inline void setName(const std::string& newName);
    inline bool isVisible() const;
    inline void setVisible(bool visibility);

protected:

    template<class T>
    bool readOptionalAttribute(const Node& node, const char* attrName, T& value) const;
    template<class T>
    bool readMandatoryAttribute(const Node& node, const char* attrName, T& value) const;

    std::string getType(const Node& node);

    // Sprites
    struct SpriteProperties {
        std::string name;
        glm::ivec2 pos;
        glm::ivec2 size;
    };
    bool readSpriteProperties(const Node& node, const char* name,
                              SpriteProperties& properties) const;
    std::shared_ptr<Sprite> createSprite(const SpriteProperties& properties);

    // AABB
    struct AABB {
        glm::ivec2 leftTop{0, 0};
        glm::ivec2 rightBottom{0, 0};
        glm::vec4 relative{0.f};

        inline bool check(int x, int y) {
            return leftTop.x <= x && x <= rightBottom.x
                && leftTop.y <= y && y <= rightBottom.y;
        }
    };
    void updateScreenCoordinates(AABB& aabb) const;
    AABB screenCoordinates;

    // Properties
    std::string name;
    const Widget* parent;
    glm::ivec2 position{0, 0};
    glm::ivec2 size{0, 0};
    bool visible{true};
};


// ---------------------------------------------------------------------

inline const std::string ui::Widget::getName() const {
    return name;
}

inline void ui::Widget::setName(const std::string& newName) {
    name = newName;
}

inline bool ui::Widget::isVisible() const {
    return visible;
}

inline void ui::Widget::setVisible(bool visibility) {
    visible = visibility;
}

// ---------------------------------------------------------------------

template<class T>
inline bool ui::Widget::readOptionalAttribute(const Node& node, const char* attrName, T& value) const {
    if (!node.HasMember(attrName))
        return true;
    else
        return readMandatoryAttribute<T>(node, attrName, value);
}

template<class T>
inline bool ui::Widget::readMandatoryAttribute(const Node& node, const char* attrName, T& value) const {
        return false;
}

template<>
inline bool ui::Widget::readMandatoryAttribute<bool>(const Node& node, const char* attrName, bool& value) const {
    if (!node.HasMember(attrName) || !node[attrName].IsBool())
        return false;
    value = node[attrName].GetBool();
    return true;
}

template<>
inline bool ui::Widget::readMandatoryAttribute<std::string>(const Node& node, const char* attrName, std::string& value) const {
    if (!node.HasMember(attrName) || !node[attrName].IsString())
        return false;
    value = node[attrName].GetString();
    return true;
}

template<>
inline bool ui::Widget::readMandatoryAttribute<glm::ivec2>(const Node& node, const char* attrName, glm::ivec2& value) const {
    if (!node.HasMember(attrName) || !node[attrName].IsArray() || node[attrName].Size() != 2)
        return false;

    const auto& arr = node[attrName];
    for (size_t i = 0; i < arr.Size(); i++) {
        if (!arr[i].IsNumber())
            return false;
        value[i] = arr[i].GetInt();
    }
    return true;
}

} // namespace ui


#endif //SOKOBAN_WIDGET_H
