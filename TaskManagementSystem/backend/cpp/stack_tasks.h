#ifndef STACK_TASKS_H
#define STACK_TASKS_H

#include <sstream>
#include <string>
#include <vector>
#include "task.h"

class StackTasks {
    std::vector<Task> st;

   public:
    void push(const Task& t) { st.push_back(t); }

    bool pop() {
        if (st.empty()) return false;
        st.pop_back();
        return true;
    }

    bool remove(int id) {
        for (size_t i = 0; i < st.size(); i++) {
            if (st[i].id == id) {
                st.erase(st.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool update(const Task& t) {
        for (Task& item : st) {
            if (item.id == t.id) {
                item = t;
                return true;
            }
        }
        return false;
    }

    const Task* search(int id) const {
        for (const Task& t : st) {
            if (t.id == id) return &t;
        }
        return nullptr;
    }

    std::string display() const {
        if (st.empty()) return "No tasks found";
        std::ostringstream os;
        for (auto it = st.rbegin(); it != st.rend(); ++it) os << taskToString(*it) << "\n";
        return os.str();
    }
};

#endif
