#ifndef SOKOBAN_UI_H
#define SOKOBAN_UI_H

#include "../core/imanager.h"
#include "../core/eventlistener.h"
#include "../core/commandhandler.h"
#include <memory>


namespace ui {

class UiImpl;

class Ui : public IManager, public CommandHandler, public EventListener {
public:
    Ui(int width, int height);
    ~Ui() override;

    bool init(const std::string& json);

    void draw() const;

    // -- EventListener ---------------------
    bool onMouseDown(const MouseEvent& event) override;
    bool onMouseUp(const MouseEvent& event) override;
    bool onMouseMove(const MouseEvent& event) override;
    bool onKeyDown(const KeyEvent& event) override;
    bool onKeyUp(const KeyEvent& event) override;

private:
    UiImpl* pImpl{nullptr};
};

} // namespace ui

#endif //SOKOBAN_UI_H
