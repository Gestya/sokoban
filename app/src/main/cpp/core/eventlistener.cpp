#include "eventlistener.h"
#include "../appcore.h"
#include "eventmanager.h"
#include <cassert>


EventListener::EventListener (bool toFront /* = false */) {
    auto eventManager = AppCore::getInstance().getEventManager();
    assert(eventManager);
    eventManager->subscribe(this, toFront);
}

EventListener::~EventListener() {
    auto eventManager = AppCore::getInstance().getEventManager();
    assert(eventManager);
    eventManager->unsubscribe(this);
}


bool EventListener::onMouseDown(const MouseEvent& event) {
    return false;
}

bool EventListener::onMouseUp(const MouseEvent& event) {
    return false;
}

bool EventListener::onMouseMove(const MouseEvent& event) {
    return false;
}

bool EventListener::onKeyDown(const KeyEvent& event) {
    return false;
}

bool EventListener::onKeyUp(const KeyEvent& event) {
    return false;
}