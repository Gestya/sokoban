#include "factory.h"

#include "objects/wall.h"
#include "objects/space.h"
#include "objects/dude.h"
#include "objects/box.h"
#include "objects/target.h"

game::Factory::Factory() {
    registration(ObjectId::Wall,
                 []() { return std::make_unique<Wall>(); },
                 []() { return nullptr; } );
    registration(ObjectId::Space,
                 []() { return std::make_unique<Space>(); },
                 []() { return nullptr; } );
    registration(ObjectId::Dude,
                 []() { return std::make_unique<Space>(); },
                 []() { return std::make_unique<Dude>(); } );
    registration(ObjectId::Box,
                 []() { return std::make_unique<Space>(); },
                 []() { return std::make_unique<Box>(); } );
    registration(ObjectId::Target,
                 []() { return std::make_unique<Space>(); },
                 []() { return std::make_unique<Target>(); } );
}

game::Factory::Product game::Factory::produce(ObjectId id) {
    auto it = producers.find(id);
    assert(it != producers.end());

    auto producers = it->second;
    return { std::move(producers.first()), std::move(producers.second()) };
}

void game::Factory::registration(ObjectId id, Producer background, Producer foreground) {
    auto it = producers.find(id);
    assert(it == producers.end());

    producers[id] = std::pair<Producer, Producer>(background, foreground);
}