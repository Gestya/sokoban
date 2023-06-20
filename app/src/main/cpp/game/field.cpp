#include "field.h"
#include "factory.h"
#include "../appcore.h"
#include "../graphics/renderer.h"
#include "objects/box.h"


void game::Field::init(const std::vector<std::vector<char>>& depiction) {
    if (!setSize(depiction)) {
        clear();
        return; // Error
    }

    labyrinth.reserve(fieldSize.x * fieldSize.y);

    for (size_t y = 0; y < fieldSize.y; ++y) {
        assert(depiction[y].size() == fieldSize.x);
        for (size_t x = 0; x < fieldSize.x; ++x) {
            ObjectId id = static_cast<ObjectId>(depiction[y][x]);
            Factory::Product cell{ std::move(Factory::getInstance().produce(id)) };
            glm::ivec2 pos{static_cast<int>(x), static_cast<int>(y)};
            if (!appendLabyrinth(std::move(cell.first), pos)
                || !appendObjects(std::move(cell.second), pos)) {
                clear();
                return; // Error
            }
        }
    }

    if (!createModels()) {
        clear();
        return; // Error
    }

    valid = true;
}


void game::Field::clear() {
    labyrinth.clear();
    targets.clear();
    boxes.clear();
    dude.clear();

    fieldSize = {-1, -1};

    valid = {false};
}


void game::Field::moveDude(const glm::ivec2& direction) {
    if (!valid)
        return;

    auto newDudePos = dude[0]->getPosition() + direction;
    size_t kdd = newDudePos.y * fieldSize.x + newDudePos.x;
    if (labyrinth[kdd]->getId() != ObjectId::Space)
        return;

    auto box = getObjectByPosition(boxes, newDudePos);
    if (!box) {
        dude[0]->setPosition(newDudePos);
        createAnimatedMove(dude[0]->getModel(), newDudePos);
    }
    else {
        auto newBoxPos = newDudePos + direction;
        size_t kbx = newBoxPos.y * fieldSize.x + newBoxPos.x;
        if (labyrinth[kbx]->getId() == ObjectId::Space
            && !getObjectByPosition(boxes, newBoxPos)) {
            box->setPosition(newBoxPos);
            createAnimatedMove(box->getModel(), newBoxPos);
            dude[0]->setPosition(newDudePos);
            createAnimatedMove(dude[0]->getModel(), newDudePos);

            auto target = getObjectByPosition(targets, newBoxPos);
            static_cast<Box*>(box)->setHighlighted(target);
        }
    }
}


bool game::Field::isCompleted() const {
    for (size_t i = 0; i < boxes.size(); i++) {
        Box* box = static_cast<Box*>(boxes[i].get());
        if (!box->isHighlighted())
            return false;
    }
    return true;
}


bool game::Field::setSize(const std::vector<std::vector<char>>& depiction) {
    fieldSize.y = depiction.size();
    if (fieldSize.y == 0)
        return false;

    fieldSize.x = depiction[0].size();
    if (fieldSize.x == 0)
        return false;

    return true;
}


void game::Field::addToVector(std::vector<UptrObject>& vct, UptrObject&& object, const glm::ivec2& pos) {
    vct.emplace_back(std::move(object));
    Object& lastOne = *vct.back();
    lastOne.setPosition(pos);
}


bool game::Field::appendLabyrinth(UptrObject&& object, const glm::ivec2& pos) {
    if (object) {
        addToVector(labyrinth, std::move(object), pos);
        return true;
    }

    return false;  // Mustn't be empty
}


bool game::Field::appendObjects(UptrObject&& object, const glm::ivec2& pos) {
    if (object) {
        std::vector<UptrObject>* vct{nullptr};
        switch(object->getId()) {
            case ObjectId::Dude:
                if (dude.size())
                    return false;  // Error: second Dude is detected
                vct = &dude;
                break;
            case ObjectId::Box:
                vct = &boxes;
                break;
            case ObjectId::Target:
                vct = &targets;
                break;
            default:
                break;
        }
        if (vct) {
            addToVector(*vct, std::move(object), pos);
        }
    }
    return true;
}


bool game::Field::createModels() {
    Renderer* renderer = AppCore::getInstance().getRenderer();
    if (!renderer)
        return false;

    auto processVector = [renderer](const std::vector<UptrObject>& vct) {
        for (size_t i = 0; i < vct.size(); i++) {
            auto& obj = *vct[i];
            auto model = std::make_shared<Mesh>();
            model->setTexture(renderer->getTexture(obj.getTextureName()));
            model->setScale(obj.getScale());
            model->setTranslate(obj.getTranslate());
            model->setPosition(obj.getPosition());
            obj.setModel(model);
            renderer->addModel3d(model);
        }
    };

    processVector(boxes);
    processVector(dude);
    processVector(targets);
    processVector(labyrinth);

    return true;
}


game::Object* game::Field::getObjectByPosition(const std::vector<UptrObject>& vct, const glm::ivec2& pos) {
    for (size_t i = 0; i < vct.size(); i++) {
        if (vct[i]->getPosition() == pos)
            return &(*vct[i]);
    }
    return nullptr;
}


void game::Field::createAnimatedMove(Mesh* model, const glm::ivec2& moveTo) {
    glm::vec2 oldPos {model->getPosition()};
    glm::vec2 newPos {moveTo};

    Task::Updater modelUpdater = [model, oldPos, newPos](const double &value, const double &time) {
        const glm::vec2& pos{oldPos + (newPos - oldPos) * static_cast<float>(value)};
        model->setPosition(pos);
    };

    createTask(std::make_unique<Task>(0.2, modelUpdater, curves::Logarithmic));
}