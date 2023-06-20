#ifndef SOKOBAN_FACTORY_H
#define SOKOBAN_FACTORY_H

#include <string>
#include <map>
#include "widgets/widget.h"


namespace ui {

class Factory {
    using Creator = std::function<SptrWidget(const Widget*, const std::string&)>;

public:
    static const Factory& getInstance() {
        static Factory instance;
        return instance;
    }

    bool create(Widget* parent, const std::string& type, const std::string& name, const Node& node) const;

private:
    Factory();

    std::map<std::string, Creator> creators;
};

} // namespace ui




#endif //SOKOBAN_FACTORY_H
