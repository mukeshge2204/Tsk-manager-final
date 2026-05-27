#ifndef QUEUE_TASKS_H
#define QUEUE_TASKS_H

#include <deque>
#include <sstream>
#include <string>
#include "task.h"

class QueueTasks {
    std::deque<Task> q;

   public:
    void enqueue(const Task& t) { q.push_back(t); }

    bool dequeue() {
        if (q.empty()) return false;
        q.pop_front();
        return true;
    }

    bool remove(int id) {
        for (size_t i = 0; i < q.size(); i++) {
            if (q[i].id == id) {
                q.erase(q.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool update(const Task& t) {
        for (Task& item : q) {
            if (item.id == t.id) {
                item = t;
                return true;
            }
        }
        return false;
    }

    const Task* search(int id) const {
        for (const Task& t : q) {
            if (t.id == id) return &t;
        }
        return nullptr;
    }

    std::string display() const {
        if (q.empty()) return "No tasks found";
        std::ostringstream os;
        for (const Task& t : q) os << taskToString(t) << "\n";
        return os.str();
    }
};

#endif
