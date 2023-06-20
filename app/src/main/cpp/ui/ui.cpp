#include "ui.h"
#include "widgets/desktop.h"
#include "../rapidjson/document.h"
#include "../rapidjson/error/error.h"
#include "../rapidjson/error/en.h"
#include "../AndroidOut.h"
#include "../appcore.h"
#include "../core/commandmanager.h"


// TODO : move it to a JSON file
#include "json.cpp"


namespace ui {

class UiImpl : public CommandHandler {
    friend class Ui;

    UiImpl(int width, int height);

    bool init(const std::string& json);
    void draw() const;

    void onConfirmShow();
    void onConfirmYes();
    void onConfirmNo();
    void onGameStart();
    void onGameWin();

    void setVisibility(const std::string& name, bool flag);

    std::unique_ptr<Desktop> desktop;

    bool isConfirmActive{false};
};

} // namespace ui

// ----------------------------------------------------------------------------------------
// UI

ui::Ui::Ui(int width, int height)
    : EventListener(true) {
    pImpl = new UiImpl(width, height);
}

ui::Ui::~Ui() {
    delete pImpl;
}

bool ui::Ui::init(const std::string& json) {
    return (pImpl) ? pImpl->init(json) : false;
}

void  ui::Ui::draw() const {
    if (pImpl)
        pImpl->draw();
}

bool ui::Ui::onMouseDown(const MouseEvent& event) {
    return (pImpl && pImpl->desktop) ? pImpl->desktop->onMouseDown(event) : false;
}
bool ui::Ui::onMouseUp(const MouseEvent& event) {
    return (pImpl && pImpl->desktop) ? pImpl->desktop->onMouseUp(event) : false;
}
bool ui::Ui::onMouseMove(const MouseEvent& event) {
    return (pImpl && pImpl->desktop) ? pImpl->desktop->onMouseMove(event) : false;
}
bool ui::Ui::onKeyDown(const KeyEvent& event) {
    return (pImpl && pImpl->desktop) ? pImpl->desktop->onKeyDown(event) : false;
}
bool ui::Ui::onKeyUp(const KeyEvent& event) {
    return (pImpl && pImpl->desktop) ? pImpl->desktop->onKeyUp(event) : false;
}

// ----------------------------------------------------------------------------------------
// UI Impl
ui::UiImpl::UiImpl(int width, int height) {
    desktop = std::make_unique<ui::Desktop>(width, height);
    if (!init(JSON))
        desktop.reset();

    if (desktop) {
        auto *commandManager = AppCore::getInstance().getCommandManager();
        commandManager->registerCommand("ui.confirm.show", this, CommandManager::Executor(&ui::UiImpl::onConfirmShow));
        commandManager->registerCommand("ui.confirm.yes", this, CommandManager::Executor(&ui::UiImpl::onConfirmYes));
        commandManager->registerCommand("ui.confirm.no", this, CommandManager::Executor(&ui::UiImpl::onConfirmNo));
        commandManager->registerCommand("ui.game.start", this, CommandManager::Executor(&ui::UiImpl::onGameStart));
        commandManager->registerCommand("ui.game.win", this, CommandManager::Executor(&ui::UiImpl::onGameWin));

        commandManager->bindKey(KeyCodes::KeyR, "ui.confirm.show");
        commandManager->bindKey(KeyCodes::KeyEnter, "ui.confirm.yes");
        commandManager->bindKey(KeyCodes::KeyEsc, "ui.confirm.no");
    }
}

bool ui::UiImpl::init(const std::string& json) {
    using namespace rapidjson;
    Document doc;
    ParseResult result = doc.Parse(json.c_str());
    if (!result) {
        // TODO : search for a line with error and show it
        aout << "JSON parse error: " << GetParseError_En(doc.GetParseError());
        aout << " (" << result.Offset() << ")" << std::endl;
        return false;
    }

    if (!doc.IsObject())
        return false;

    return desktop->init(doc.GetObject());
}

void ui::UiImpl::draw() const {
    if (desktop)
        desktop->draw();
}

void ui::UiImpl::onConfirmShow() {
    isConfirmActive = true;
    setVisibility("ConfirmWindow", true);
}

void ui::UiImpl::onConfirmYes() {
    if (!isConfirmActive)
        return;

    isConfirmActive = false;
    setVisibility("ConfirmWindow", false);
    AppCore::getInstance().getCommandManager()->invokeCommand("level.restart");
}

void ui::UiImpl::onConfirmNo() {
    if (!isConfirmActive)
        return;

    isConfirmActive = false;
    setVisibility("ConfirmWindow", false);
}

void ui::UiImpl::onGameStart() {
    setVisibility("ConfirmWindow", false);
    setVisibility("WinningWindow", false);
}

void ui::UiImpl::onGameWin() {
    setVisibility("ConfirmWindow", false);
    setVisibility("WinningWindow", true);
}

void ui::UiImpl::setVisibility(const std::string& name, bool flag) {
    if (desktop) {
        Widget *window = desktop->findByName(name);
        if (window)
            window->setVisible(flag);
    }
}
