#include "taskmanager.h"
#include "../appcore.h"
#include <cassert>


// ----------------------------------------------------------------------------------------
// TaskProvider

TaskProvider::TaskProvider() {
    auto taskManager = AppCore::getInstance().getTaskManager();
    assert(taskManager);
    taskManager->subscribe(*this);
}

TaskProvider::~TaskProvider() {
    auto taskManager = AppCore::getInstance().getTaskManager();
    assert(taskManager);
    taskManager->unsubscribe(*this);
}

void TaskProvider::createTask(std::unique_ptr<Task>&& task) {
    auto taskManager = AppCore::getInstance().getTaskManager();
    assert(taskManager);
    taskManager->addTask(this, std::move(task));
}

// ----------------------------------------------------------------------------------------
// TaskManager

TaskManager::~TaskManager() {
    providers.clear();
    assert(tasks.size() == 0);
}

void TaskManager::subscribe(const TaskProvider& provider) {
    auto it = std::find(providers.begin(), providers.end(), &provider);
    assert(it == providers.end());
    if (it == providers.end()) {
        providers.push_back(&provider);
    }
}

void TaskManager::unsubscribe(const TaskProvider& provider) {
    auto it = std::find(providers.begin(), providers.end(), &provider);
    assert(it != providers.end());
    if (it != providers.end()) {
        cleanUp(provider);
        providers.erase(it);
    }
}

void TaskManager::addTask(const TaskProvider* owner, std::unique_ptr<Task>&& task) {
    tasks.emplace_back(TaskWithOwner{owner, std::move(task)});
}

void TaskManager::update() {
    auto it = tasks.begin();
    while (it != tasks.end()) {
        Task& task = *(it->second);
        auto lastUpdated = it++;
        if (task.update()) { // completed?
            tasks.erase(lastUpdated);
        }
    }
}

void TaskManager::cleanUp(const TaskProvider& provider) {
    auto it = tasks.begin();
    while (it != tasks.end()) {
        Task& task = *(it->second);
        if (it->first == &provider) {
            auto erasing = it++;
            tasks.erase(erasing);
        }
    }
}
