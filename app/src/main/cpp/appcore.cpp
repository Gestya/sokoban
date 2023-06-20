#include "appcore.h"
#include "graphics/renderer.h"
#include "game/manager.h"
#include "core/eventmanager.h"
#include "core/taskmanager.h"
#include "core/commandmanager.h"
#include "ui/ui.h"

#include <game-activity/native_app_glue/android_native_app_glue.h>


class AppCoreImpl {
    friend class AppCore;

    bool init(struct android_app *pApp);
    bool shutdown();

    inline void handleInput();
    inline void update();
    inline void render();

    inline Renderer* getRenderer();
    inline EventManager* getEventManager();
    inline TaskManager* getTaskManager();
    inline CommandManager* getCommandManager();
    inline game::Manager* getGameManager();
    inline ui::Ui* getUi();

    struct android_app* androidApp{nullptr};
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<EventManager> eventManager;
    std::unique_ptr<TaskManager> taskManager;
    std::unique_ptr<CommandManager> commandManager;
    std::unique_ptr<game::Manager> gameManager;
    std::unique_ptr<ui::Ui> ui;
};

// ----------------------------------------------------------------------------------------
// AppCore

bool AppCore::init(struct android_app *pApp) {
    if (!pImpl) {
        pImpl = new AppCoreImpl();
        return pImpl->init(pApp);
    }

    return false;
}

bool AppCore::shutdown() {
    if (pImpl) {
        return pImpl->shutdown();
        delete pImpl;
        pImpl = nullptr;
    }

    return false;
}

void AppCore::handleInput() {
    if (pImpl)
        pImpl->handleInput();
}

void AppCore::update() {
    if (pImpl)
        pImpl->update();
}

void AppCore::render() {
    if (pImpl)
        pImpl->render();
}

Renderer* AppCore::getRenderer() {
    return pImpl ? pImpl->getRenderer() : nullptr;
}
EventManager* AppCore::getEventManager() {
    return pImpl ? pImpl->getEventManager() : nullptr;
}
TaskManager* AppCore::getTaskManager() {
    return pImpl ? pImpl->getTaskManager() : nullptr;
}
CommandManager* AppCore::getCommandManager() {
    return pImpl ? pImpl->getCommandManager() : nullptr;
}
game::Manager* AppCore::getGameManager() {
    return pImpl ? pImpl->getGameManager() : nullptr;
}
ui::Ui* AppCore::getUi() {
    return pImpl ? pImpl->getUi() : nullptr;
}

// ----------------------------------------------------------------------------------------
// AppCoreImpl

bool AppCoreImpl::init(struct android_app *pApp) {
    androidApp = pApp;
    // The order matters!!!
    taskManager = std::make_unique<TaskManager>();      // 1st
    eventManager = std::make_unique<EventManager>();    // 2nd
    commandManager = std::make_unique<CommandManager>();
    renderer = std::make_unique<Renderer>(androidApp);
    gameManager = std::make_unique<game::Manager>();
    auto screenSize = renderer->getScreenSize();
    ui = std::make_unique<ui::Ui>(screenSize.x, screenSize.y);
    return true;
}

bool AppCoreImpl::shutdown() {
    androidApp = nullptr;
    // The order matters!!!
    ui.reset();
    gameManager.reset();
    renderer.reset();
    commandManager.reset();
    eventManager.reset();       // Penultimate
    taskManager.reset();        // Last
    return true;
}

inline void AppCoreImpl::handleInput() {
    if (eventManager)
        eventManager->handleInput(androidApp);
}

inline void AppCoreImpl::update() {
    if (taskManager)
        taskManager->update();
}

inline void AppCoreImpl::render() {
    if (ui)
        ui->draw();
    if (renderer)
        renderer->render();
}

inline Renderer* AppCoreImpl::getRenderer() {
    return &(*renderer);
}
inline EventManager* AppCoreImpl::getEventManager() {
    return &(*eventManager);
}
inline TaskManager* AppCoreImpl::getTaskManager() {
    return &(*taskManager);
}
inline CommandManager* AppCoreImpl::getCommandManager() {
    return &(*commandManager);
}
inline game::Manager* AppCoreImpl::getGameManager() {
    return &(*gameManager);
}
inline ui::Ui* AppCoreImpl::getUi() {
    return &(*ui);
}
