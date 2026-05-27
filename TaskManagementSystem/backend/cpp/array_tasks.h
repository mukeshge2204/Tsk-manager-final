#ifndef ARRAY_TASKS_H
#define ARRAY_TASKS_H

#include <sstream>
#include <string>
#include <vector>
#include "task.h"

class ArrayTasks {
    std::vector<Task> tasks;

   public:
    void add(const Task& t) { tasks.push_back(t); }

    bool remove(int id) {
        for (size_t i = 0; i < tasks.size(); i++) {
            if (tasks[i].id == id) {
                tasks.erase(tasks.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool update(const Task& t) {
        for (Task& item : tasks) {
            if (item.id == t.id) {
                item = t;
                return true;
            }
        }
        return false;
    }

    const Task* search(int id) const {
        for (const Task& t : tasks) {
            if (t.id == id) return &t;
        }
        return nullptr;
    }

    std::string display() const {
        std::ostringstream os;
        if (tasks.empty()) return "No tasks found";
        for (const Task& t : tasks) os << taskToString(t) << "\n";
        return os.str();
    }
};

#endif
