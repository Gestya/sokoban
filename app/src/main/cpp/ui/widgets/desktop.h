#ifndef SOKOBAN_DESKTOP_H
#define SOKOBAN_DESKTOP_H

#include "window.h"


namespace ui {

class Desktop : public Window {
public:
    Desktop(int width, int height);

    bool init(const Node& node);

    bool onMouseDown(const MouseEvent& event) override;
    bool onMouseUp(const MouseEvent& event) override;
    bool onMouseMove(const MouseEvent& event) override;

    // TODO : this is a right approach but terrible implementation!!!
    static Widget* CapturedWidget;
};

} // namespace ui

#endif //SOKOBAN_DESKTOP_H
