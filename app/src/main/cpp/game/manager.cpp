#include "manager.h"
#include "../appcore.h"
#include "../graphics/renderer.h"
#include "../core/commandmanager.h"
#include <vector>


static std::vector<std::vector<char>> depiction = {
        {'W', 'W', 'W', 'W', 'W', 'W', 'W'},
        {'W', 'W', 'D', 'S', 'W', 'W', 'W'},
        {'W', 'S', 'B', 'S', 'W', 'W', 'W'},
        {'W', 'S', 'S', 'B', 'S', 'T', 'W'},
        {'W', 'W', 'S', 'S', 'T', 'S', 'W'},
        {'W', 'W', 'W', 'W', 'W', 'W', 'W'}
};

game::Manager::Manager() {
    auto* commandManager = AppCore::getInstance().getCommandManager();

    commandManager->registerCommand("move.up", this, CommandManager::Executor(&Manager::onUp));
    commandManager->bindKey(KeyCodes::KeyUp, "move.up");
    commandManager->registerCommand("move.down", this, CommandManager::Executor(&Manager::onDown));
    commandManager->bindKey(KeyCodes::KeyDown, "move.down");
    commandManager->registerCommand("move.left", this, CommandManager::Executor(&Manager::onLeft));
    commandManager->bindKey(KeyCodes::KeyLeft, "move.left");
    commandManager->registerCommand("move.right", this, CommandManager::Executor(&Manager::onRight));
    commandManager->bindKey(KeyCodes::KeyRight, "move.right");

    commandManager->registerCommand("level.restart", this, CommandManager::Executor(&Manager::onRestart));

    prepareNewGame();
}

void game::Manager::moveDude(const glm::ivec2& direction) {
    if (isGoing)
        gameField->moveDude(direction);
    if (gameField->isCompleted()) {
        isGoing = false;
        AppCore::getInstance().getCommandManager()->invokeCommand("ui.game.win");
    }
}

void game::Manager::onUp() {
    moveDude({0, -1});
}
void game::Manager::onDown() {
    moveDude({0, 1});
}
void game::Manager::onLeft() {
    moveDude({-1, 0});
}
void game::Manager::onRight() {
    moveDude({1, 0});
}

void game::Manager::onRestart() {
    gameField.reset();
    prepareNewGame();
}

//--------------------------------------
// TODO : remaster this stuff!!!!!!!!!!!!!
void game::Manager::prepareNewGame() {
    Renderer* renderer = AppCore::getInstance().getRenderer();
    renderer->removeModels();

    gameField = std::make_unique<Field>();
    gameField->init(depiction);

    isGoing = true;

    // TODO : this command should wait for UI is initialized.
    AppCore::getInstance().getCommandManager()->invokeCommand("ui.game.start");
}
//--------------------------------------
