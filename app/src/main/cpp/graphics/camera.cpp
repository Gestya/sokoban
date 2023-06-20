#include "camera.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../appcore.h"
#include "../core/commandmanager.h"


Camera::Camera() {
    update();

    auto *commandManager = AppCore::getInstance().getCommandManager();
    commandManager->registerCommand("camera.scroll", this, CommandManager::Executor(&Camera::onCameraScroll));
    commandManager->bindKey(KeyCodes::KeySpace, "camera.scroll");
    commandManager->registerCommand("camera.reset", this, CommandManager::Executor(&Camera::onCameraReset));
    commandManager->bindKey(KeyCodes::KeyQ, "camera.reset");
}

void Camera::init(const Settings& inSettings) {
    settings = inSettings;
    update();
}

void Camera::changeAspect(int width, int height) {
    settings.aspect = static_cast<float>(width) / static_cast<float>(height);
    update();
}

void Camera::update() {
    proj = glm::perspective(settings.fov, settings.aspect, settings.near, settings.far);
    view = glm::lookAt(settings.eye, settings.center, settings.up);
    projView = proj * view;
}

void Camera::onCameraScroll() {
    scroll = !scroll;
}

void Camera::onCameraReset() {
    auto aspect = settings.aspect;
    settings = Settings();
    settings.aspect = aspect;
    update();
}

bool Camera::onMouseDown(const MouseEvent& event) {
    mouseButton = true;
    mousePos = {event.x, -event.y};
    return true;
}

bool Camera::onMouseUp(const MouseEvent& event) {
    mouseButton = false;
    return true;
}

bool Camera::onMouseMove(const MouseEvent& event) {
    if (!mouseButton)
        return false;

    glm::vec2 mouseNewPos{event.x, -event.y};
    glm::vec2 delta = (mousePos - mouseNewPos) / 100.f;
    mousePos = mouseNewPos;

    settings.eye += glm::vec3{delta, 0.f};
    if (scroll)
        settings.center += glm::vec3{delta, 0.f};

    update();

    return true;
}