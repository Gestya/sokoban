#ifndef SOKOBAN_FIELD_H
#define SOKOBAN_FIELD_H


#include "../core/taskmanager.h"
#include "objects/object.h"
#include <vector>


namespace game {

class Field : public TaskProvider {
public:
    Field() {}
    virtual ~Field() {}

    void init(const std::vector<std::vector<char>>& depiction);
    void clear();
    bool isValid() const;

    glm::ivec2& getFieldSize();
    const glm::ivec2& getFieldSize() const;

    void moveDude(const glm::ivec2& direction);

    bool isCompleted() const;

private:
    bool setSize(const std::vector<std::vector<char>>& depiction);
    bool appendLabyrinth(UptrObject&& object, const glm::ivec2& pos);
    bool appendObjects(UptrObject&& object, const glm::ivec2& pos);
    void addToVector(std::vector<UptrObject>& vct, UptrObject&& object, const glm::ivec2& pos);
    bool createModels();
    Object* getObjectByPosition(const std::vector<UptrObject>& vct, const glm::ivec2& pos);

    void createAnimatedMove(Mesh* model, const glm::ivec2& moveTo);

    bool valid{false};

    std::vector<UptrObject> labyrinth;
    std::vector<UptrObject> targets;
    std::vector<UptrObject> boxes;
    std::vector<UptrObject> dude;  // Dude always exists in one instance,
                                // but it is better to store him in a vector.

    glm::ivec2 fieldSize{-1, -1};
};

} // namespace game


inline bool game::Field::isValid() const{
    return valid;
}
inline glm::ivec2& game::Field::getFieldSize() {
    return fieldSize;
}
inline const glm::ivec2& game::Field::getFieldSize() const {
    return fieldSize;
}


#endif //SOKOBAN_FIELD_H
