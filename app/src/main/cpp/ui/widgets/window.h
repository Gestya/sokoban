#ifndef SOKOBAN_WINDOW_H
#define SOKOBAN_WINDOW_H

#include "widget.h"


namespace ui {

class Window : public Widget {
public:
    Window(const Widget* parent, const std::string& name)
        : Widget(parent, name) { }
    ~Window() override = default;

    bool addChild(SptrWidget&& child) override;
    Children* getChildren() override;
    void draw() const override;

    bool onMouseDown(const MouseEvent& event) override;
    bool onMouseUp(const MouseEvent& event) override;
    bool onMouseMove(const MouseEvent& event) override;

protected:
    bool initWidget(const Node& node) override;
    bool createNestedWidgets(const Node& node, bool any = true);

    Children children;
};

} // namespace ui

#endif //SOKOBAN_WINDOW_H
