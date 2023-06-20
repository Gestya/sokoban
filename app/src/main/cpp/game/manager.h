#ifndef SOKOBAN_MANAGER_H
#define SOKOBAN_MANAGER_H

#include "../core/imanager.h"
#include "../core/commandhandler.h"
#include "field.h"
#include <memory>


namespace game {

class Manager : public IManager, public CommandHandler {
public:
    Manager();
    virtual ~Manager() = default;

private:
    void moveDude(const glm::ivec2& direction);

    void onUp();
    void onDown();
    void onLeft();
    void onRight();

    void onRestart();

    //--------------------------------------
    void prepareNewGame();  // TODO : remaster this stuff!!!!!!!!!!!!!
    //--------------------------------------

    std::unique_ptr<Field> gameField;
    bool isGoing{true};
};

} // namespace game

#endif //SOKOBAN_MANAGER_H
