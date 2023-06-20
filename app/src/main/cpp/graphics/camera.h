#ifndef SOKOBAN_CAMERA_H
#define SOKOBAN_CAMERA_H


#include "../glm/glm.hpp"
#include "../core/commandhandler.h"
#include "../core/eventlistener.h"


// TODO : CommandHandler & EventListener MUST NOT BE HERE!!!
class Camera : public CommandHandler, public EventListener {
public:
    struct Settings {
        float fov{45.0f};
        float aspect{1.0f};
        float near{1.0f};
        float far{150.0f};

        //glm::vec3 eye{2.1f, -6.3f, 6.0f};
        glm::vec3 eye{0.67f, -6.68f, 6.f};
        //glm::vec3 center{3.1f, -2.9f, 1.0f};
        glm::vec3 center{2.16f, -4.12, 1.f};
        glm::vec3 up{0.f, 0.f, 1.f};
    };

    Camera();

    void init(const Settings& inSettings);

    inline const glm::mat4& getProj() const;
    inline const glm::mat4& getView() const;
    inline const glm::mat4& getProjView() const;

    void changeAspect(int width, int height);

private:
    void update();

    bool onMouseDown(const MouseEvent& event) override;
    bool onMouseUp(const MouseEvent& event) override;
    bool onMouseMove(const MouseEvent& event) override;

    void onCameraScroll();
    void onCameraReset();

    bool scroll{false};
    bool mouseButton{false};
    glm::vec2 mousePos{-1.f, -1.f};

    Settings settings;

    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 projView;
};



inline const glm::mat4& Camera::getProj() const {
    return proj;
}

inline const glm::mat4& Camera::getView() const {
    return view;
}

inline const glm::mat4& Camera::getProjView() const {
    return projView;
}


#endif //SOKOBAN_CAMERA_H
