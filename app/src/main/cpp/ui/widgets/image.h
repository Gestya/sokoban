#ifndef SOKOBAN_IMAGE_H
#define SOKOBAN_IMAGE_H

#include "widget.h"


namespace ui {

class Image : public Widget {
public:
    Image(const Widget* parent, const std::string& name)
        : Widget(parent, name) { }
    ~Image() override = default;

    void draw() const override;

protected:
    bool initWidget(const Node& node) override;

    std::shared_ptr<Sprite> sprite;
};

} // namespace ui

#endif //SOKOBAN_IMAGE_H
