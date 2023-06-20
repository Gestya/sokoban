#ifndef SOKOBAN_FACTORY_H
#define SOKOBAN_FACTORY_H


#include "objects/object.h"
#include <map>
#include <cassert>
#include <memory>


namespace game {

class Factory {
public:
    using Producer = std::function<UptrObject(void)>;
    using Product = std::pair<UptrObject, UptrObject>;

    static Factory& getInstance() {
        static Factory instance;
        return instance;
    }

    Product produce(ObjectId id);

private:
    // It is singleton therefore c-tor is private
    Factory();

    void registration(ObjectId id, Producer background, Producer foreground);

    std::map<ObjectId, std::pair<Producer, Producer>> producers;
};

} // namespace game

#endif //SOKOBAN_FACTORY_H
