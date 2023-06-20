#ifndef SOKOBAN_EVENTLISTENER_H
#define SOKOBAN_EVENTLISTENER_H


enum class MouseEventType{
    MouseDown,
    MouseUp,
    MouseMove,
};

struct MouseEvent {
    int pointerId;
    float x;
    float y;
};

enum class KeyEventType{
    KeyDown,
    KeyUp,
};

struct KeyEvent {
    int keyCode;
    int scanCode;
    int unicodeChar;
};


class EventListener {
public:
    EventListener (bool toFront = false);
    virtual ~EventListener();

    virtual bool onMouseDown(const MouseEvent& event);
    virtual bool onMouseUp(const MouseEvent& event);
    virtual bool onMouseMove(const MouseEvent& event);

    virtual bool onKeyDown(const KeyEvent& event);
    virtual bool onKeyUp(const KeyEvent& event);
};


#endif //SOKOBAN_EVENTLISTENER_H
