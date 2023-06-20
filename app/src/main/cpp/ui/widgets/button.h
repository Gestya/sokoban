#ifndef SOKOBAN_BUTTON_H
#define SOKOBAN_BUTTON_H

#include "widget.h"


namespace ui {

class Button : public Widget {
public:
    Button(const Widget* parent, const std::string& name)
        : Widget(parent, name) {}
    ~Button() override = default;

    void draw() const override;

    bool onMouseDown(const MouseEvent& event) override;
    bool onMouseUp(const MouseEvent& event) override;
    bool onMouseMove(const MouseEvent& event) override;

protected:
    bool initWidget(const Node& node) override;

    bool pressed{false};
    bool disabled{false};
    std::string command;

    std::shared_ptr<Sprite> normalSprite;
    std::shared_ptr<Sprite> pressedSprite;
    std::shared_ptr<Sprite> disabledSprite;
};

} // namespace ui

#endif //SOKOBAN_BUTTON_H
