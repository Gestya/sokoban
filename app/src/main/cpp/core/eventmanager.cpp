#include "eventmanager.h"
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include "../AndroidOut.h"
#include "../appcore.h"
#include "../game/manager.h"
#include <cassert>


void EventManager::subscribe(EventListener* listener, bool toFront) {
    assert(listener);
    if (toFront)
        listeners.push_front(listener);
    else
        listeners.push_back(listener);
}

void EventManager::unsubscribe(EventListener* listener) {
    auto it = std::find(listeners.begin(), listeners.end(), listener);
    assert(it != listeners.end());
    listeners.erase(it);
}

void EventManager::handleInput(struct android_app *androidApp) {

    // handle all queued inputs
    auto *inputBuffer = android_app_swap_input_buffers(androidApp);
    if (!inputBuffer) {
        // no inputs yet.
        return;
    }

    // handle motion events (motionEventsCounts can be 0).
    for (auto i = 0; i < inputBuffer->motionEventsCount; i++) {
        auto &motionEvent = inputBuffer->motionEvents[i];
        auto action = motionEvent.action;

        // Find the pointer index, mask and bitshift to turn it into a readable value.
        auto pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
                >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
        aout << "Pointer(s): ";

        // get the x and y position of this event if it is not ACTION_MOVE.
        auto &pointer = motionEvent.pointers[pointerIndex];
        auto x = GameActivityPointerAxes_getX(&pointer);
        auto y = GameActivityPointerAxes_getY(&pointer);

        // determine the action type and process the event accordingly.
        switch (action & AMOTION_EVENT_ACTION_MASK) {
            case AMOTION_EVENT_ACTION_DOWN:
            case AMOTION_EVENT_ACTION_POINTER_DOWN:
                aout << "(" << pointer.id << ", " << x << ", " << y << ") "
                     << "Pointer Down";
                sendMouseEvent(MouseEventType::MouseDown, {pointer.id, x, y});
                break;

            case AMOTION_EVENT_ACTION_CANCEL:
                // treat the CANCEL as an UP event: doing nothing in the app, except
                // removing the pointer from the cache if pointers are locally saved.
                // code pass through on purpose.
            case AMOTION_EVENT_ACTION_UP:
            case AMOTION_EVENT_ACTION_POINTER_UP:
                aout << "(" << pointer.id << ", " << x << ", " << y << ") "
                     << "Pointer Up";
                sendMouseEvent(MouseEventType::MouseUp, {pointer.id, x, y});
                break;

            case AMOTION_EVENT_ACTION_MOVE:
                // There is no pointer index for ACTION_MOVE, only a snapshot of
                // all active pointers; app needs to cache previous active pointers
                // to figure out which ones are actually moved.
                for (auto index = 0; index < motionEvent.pointerCount; index++) {
                    pointer = motionEvent.pointers[index];
                    x = GameActivityPointerAxes_getX(&pointer);
                    y = GameActivityPointerAxes_getY(&pointer);
                    aout << "(" << pointer.id << ", " << x << ", " << y << ")";
                    sendMouseEvent(MouseEventType::MouseMove, {pointer.id, x, y});

                    if (index != (motionEvent.pointerCount - 1)) aout << ",";
                    aout << " ";
                }
                aout << "Pointer Move";
                break;
            default:
                aout << "Unknown MotionEvent Action: " << action;
        }
        aout << std::endl;
    }
    // clear the motion input count in this buffer for main thread to re-use.
    android_app_clear_motion_events(inputBuffer);

    // handle input key events.
    for (auto i = 0; i < inputBuffer->keyEventsCount; i++) {
        auto &keyEvent = inputBuffer->keyEvents[i];
        aout << "Key: " << keyEvent.keyCode <<" ";
        switch (keyEvent.action) {
            case AKEY_EVENT_ACTION_DOWN:
                aout << "Key Down";
                sendKeyEvent(KeyEventType::KeyDown,
                             {keyEvent.keyCode, keyEvent.scanCode, keyEvent.unicodeChar});
                break;
            case AKEY_EVENT_ACTION_UP:
                aout << "Key Up";
                sendKeyEvent(KeyEventType::KeyUp,
                             {keyEvent.keyCode, keyEvent.scanCode, keyEvent.unicodeChar});
                break;
            case AKEY_EVENT_ACTION_MULTIPLE:
                // Deprecated since Android API level 29.
                aout << "Multiple Key Actions";
                break;
            default:
                aout << "Unknown KeyEvent Action: " << keyEvent.action;
        }
        aout << "Repeat counter: " << keyEvent.repeatCount;
        aout << std::endl;
    }
    // clear the key input count too.
    android_app_clear_key_events(inputBuffer);
}

void EventManager::sendMouseEvent(MouseEventType type, const MouseEvent& event) {
    // TODO : What is this?! And why?!
    static constexpr float KX = 2560.f / 2558.f;
    static constexpr float KY = 1672.f / 1798.f;

    auto normalizedEvent{event};
    normalizedEvent.x *= KX;
    normalizedEvent.y *= KY;

    bool response{false};
    for (auto &listener : listeners) {
        switch (type) {
            case MouseEventType::MouseDown:
                response = listener->onMouseDown(normalizedEvent);
                break;
            case MouseEventType::MouseUp:
                response = listener->onMouseUp(normalizedEvent);
                break;
            case MouseEventType::MouseMove:
                response = listener->onMouseMove(normalizedEvent);
                break;
            default:
                // TODO : Error happened!
                break;
        }
        if (response)
            return;
    }
}

void EventManager::sendKeyEvent(KeyEventType type, const KeyEvent& event) {
    bool response{false};
    for (auto &listener : listeners) {
        switch (type) {
            case KeyEventType::KeyDown:
                response = listener->onKeyDown(event);
                break;
            case KeyEventType::KeyUp:
                response = listener->onKeyUp(event);
                break;
            default:
                // TODO : Error happened!
                break;
        }
        if (response)
            return;
    }
}