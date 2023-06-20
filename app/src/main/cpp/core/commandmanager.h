#ifndef SOKOBAN_COMMANDMANAGER_H
#define SOKOBAN_COMMANDMANAGER_H

#include "imanager.h"
#include "commandhandler.h"
#include "eventlistener.h"
#include <string>
#include <map>
#include <vector>


enum class KeyCodes {
    // __?__
    KeyEsc= 4,
    // __?__
    KeyUp = 19,
    KeyDown = 20,
    KeyLeft = 21,
    KeyRight = 22,
    // __?__
    KeyA = 29,
    KeyB = 30,
    KeyC = 31,
    KeyD = 32,
    KeyE = 33,
    KeyF = 34,
    KeyG = 35,
    KeyH = 36,
    KeyI = 37,
    KeyJ = 38,
    KeyK = 39,
    KeyL = 40,
    KeyM = 41,
    KeyN = 42,
    KeyO = 43,
    KeyP = 44,
    KeyQ = 45,
    KeyR = 46,
    KeyS = 47,
    KeyT = 48,
    KeyU = 49,
    KeyV = 50,
    KeyW = 51,
    KeyX = 52,
    KeyY = 53,
    KeyZ = 54,
    // __?__
    KeySpace = 62,
    // __?__
    KeyEnter = 66,
    // __?__
};

class CommandManager : public IManager, public EventListener {
public:
    CommandManager() = default;
    virtual ~CommandManager() = default;

    typedef void (CommandHandler::*Executor)(void);
    typedef size_t CmdHash;

    bool registerCommand(const std::string& command, CommandHandler* handler, Executor executor);
    bool bindKey(KeyCodes key, const std::string& command);
    bool invokeCommand(const std::string& command) const;

    virtual bool onKeyDown(const KeyEvent& event);

private:
    bool invokeCommand(const CmdHash& hash) const;

    std::map<CmdHash, std::pair<CommandHandler*, Executor>> commands;
    std::vector<CmdHash> boundKeys;
};


#endif //SOKOBAN_COMMANDMANAGER_H
