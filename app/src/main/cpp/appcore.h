#ifndef SOKOBAN_APPCORE_H
#define SOKOBAN_APPCORE_H


// Forward declarations
class AppCoreImpl;
class Renderer;
class EventManager;
class TaskManager;
class CommandManager;
namespace game {
    class Manager;
}
namespace ui {
    class Ui;
}

// Android application
struct android_app;


class AppCore {
public:
    static AppCore& getInstance() {
        static AppCore instance;
        return instance;
    }

    bool init(struct android_app *pApp);
    bool shutdown();

    void handleInput();
    void update();
    void render();

    Renderer* getRenderer();
    EventManager* getEventManager();
    TaskManager* getTaskManager();
    CommandManager* getCommandManager();
    game::Manager* getGameManager();
    ui::Ui* getUi();

private:
    // It is a singleton
    AppCore() = default;

    AppCoreImpl* pImpl{nullptr};
};


#endif //SOKOBAN_APPCORE_H
