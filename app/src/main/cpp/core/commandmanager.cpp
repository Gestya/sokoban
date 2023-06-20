#include "commandmanager.h"
#include <functional>


bool CommandManager::registerCommand(const std::string& command, CommandHandler* handler, Executor executor) {
    const CmdHash hash = std::hash<std::string>{}(command);
    auto it = commands.find(hash);
    if (it != commands.end())
        return false;

    commands[hash] = {handler, executor};
    return true;
}

bool CommandManager::bindKey(KeyCodes key, const std::string& command) {
    const CmdHash hash = std::hash<std::string>{}(command);
    if (commands.find(hash) == commands.end())
        return false;

    size_t uKey = static_cast<size_t>(key);
    if (boundKeys.size() < uKey + 1)
        boundKeys.resize(uKey + 1);
    boundKeys[uKey] = hash;
    return true;
}

bool CommandManager::invokeCommand(const std::string& command) const {
    const CmdHash hash = std::hash<std::string>{}(command);
    return invokeCommand(hash);
}

bool CommandManager::invokeCommand(const CmdHash& hash) const {
    auto it = commands.find(hash);
    if (it == commands.end())
        return false;

    CommandHandler* handler = (it->second).first;
    Executor executor = (it->second).second;
    (handler->*executor)();
    return true;
}

bool CommandManager::onKeyDown(const KeyEvent& event) {
    size_t uKey = static_cast<size_t>(event.keyCode);
    if (uKey < boundKeys.size())
        return invokeCommand(boundKeys[uKey]);
    else
        return false;
}
