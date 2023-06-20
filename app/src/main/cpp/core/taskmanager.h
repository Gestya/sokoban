#ifndef SOKOBAN_TASKMANAGER_H
#define SOKOBAN_TASKMANAGER_H


#include "imanager.h"
#include <list>
#include <memory>
#include "task.h"


class TaskProvider {
public:
    TaskProvider();
    virtual ~TaskProvider();

    void createTask(std::unique_ptr<Task>&& task);
};


class TaskManager : public IManager  {
public:
    TaskManager() = default;
    ~TaskManager();

    void subscribe(const TaskProvider& provider);
    void unsubscribe(const TaskProvider& provider);

    void addTask(const TaskProvider* owner, std::unique_ptr<Task>&& task);

    void update();

private:
    void cleanUp(const TaskProvider& provider);

    using TaskWithOwner = std::pair<const TaskProvider*, std::unique_ptr<Task>>;
    std::list<TaskWithOwner> tasks;
    std::list<const TaskProvider*> providers;
};


#endif //SOKOBAN_TASKMANAGER_H
