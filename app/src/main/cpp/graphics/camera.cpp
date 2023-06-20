#include "camera.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../appcore.h"
#include "../core/commandmanager.h"

#include "../AndroidOut.h"  // Debug


Camera::Camera() {
    recalculate();

    auto *commandManager = AppCore::getInstance().getCommandManager();
    commandManager->registerCommand("camera.scroll", this, CommandManager::Executor(&Camera::onCameraScroll));
    commandManager->bindKey(KeyCodes::KeySpace, "camera.scroll");
}

void Camera::init(const Settings& inSettings) {
    settings = inSettings;
    recalculate();
}

void Camera::changeAspect(int width, int height) {
    settings.aspect = static_cast<float>(width) / static_cast<float>(height);
    recalculate();
}

void Camera::recalculate() {
    proj = glm::perspective(settings.fov, settings.aspect, settings.near, settings.far);
    view = glm::lookAt(settings.eye, settings.center, settings.up);
    projView = proj * view;
}

void Camera::onCameraScroll() {
    scroll = !scroll;
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

    // Debug
    aout << std::endl;
    aout << "EYE  X = " << settings.eye.x << " Y = " << settings.eye.y << " Z = " << settings.eye.z << std::endl;
    aout << "CENTER  X = " << settings.center.x << " Y = " << settings.center.y << " Z = " << settings.center.z << std::endl;

    recalculate();

    return true;
}