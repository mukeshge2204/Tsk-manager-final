#ifndef DEQUE_TASKS_H
#define DEQUE_TASKS_H

#include <deque>
#include <sstream>
#include <string>
#include "task.h"

class DequeTasks {
    std::deque<Task> dq;

   public:
    void pushBack(const Task& t) { dq.push_back(t); }
    void pushFront(const Task& t) { dq.push_front(t); }

    bool popBack() {
        if (dq.empty()) return false;
        dq.pop_back();
        return true;
    }

    bool popFront() {
        if (dq.empty()) return false;
        dq.pop_front();
        return true;
    }

    bool remove(int id) {
        for (size_t i = 0; i < dq.size(); i++) {
            if (dq[i].id == id) {
                dq.erase(dq.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool update(const Task& t) {
        for (Task& item : dq) {
            if (item.id == t.id) {
                item = t;
                return true;
            }
        }
        return false;
    }

    const Task* search(int id) const {
        for (const Task& t : dq) {
            if (t.id == id) return &t;
        }
        return nullptr;
    }

    std::string display() const {
        if (dq.empty()) return "No tasks found";
        std::ostringstream os;
        for (const Task& t : dq) os << taskToString(t) << "\n";
        return os.str();
    }
};

#endif
