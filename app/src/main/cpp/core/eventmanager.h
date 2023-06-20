#ifndef SOKOBAN_EVENTMANAGER_H
#define SOKOBAN_EVENTMANAGER_H


#include "imanager.h"
#include "eventlistener.h"
#include <list>

// Forward declarations
struct android_app;

class EventManager : public IManager {
public:
    EventManager() = default;
    virtual ~EventManager() = default;

    void subscribe(EventListener* listener, bool toFront = false);
    void unsubscribe(EventListener* listener);

    void handleInput(struct android_app *androidApp);

private:
    void sendMouseEvent(MouseEventType type, const MouseEvent& event);
    void sendKeyEvent(KeyEventType type, const KeyEvent& event);

    std::list<EventListener*> listeners;
};


#endif //SOKOBAN_EVENTMANAGER_H
