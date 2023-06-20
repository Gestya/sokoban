//
// Created by shkap on 28-May-23.
//

#ifndef SOKOBAN_IMANAGER_H
#define SOKOBAN_IMANAGER_H


class IManager {
public:
    IManager() = default;
    virtual ~IManager() = default;

private:
    // Noncopyable
    IManager(const IManager&);
    IManager& operator=(const IManager&);
};


#endif //SOKOBAN_IMANAGER_H
