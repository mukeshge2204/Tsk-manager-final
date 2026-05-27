#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <sstream>
#include <string>
#include <vector>
#include "task.h"

class CircularQueueTasks {
    std::vector<Task> data;
    int front = 0;
    int rear = -1;
    int count = 0;

   public:
    explicit CircularQueueTasks(int capacity = 1000) : data(capacity) {}

    bool enqueue(const Task& t) {
        if (count == static_cast<int>(data.size())) return false;
        rear = (rear + 1) % static_cast<int>(data.size());
        data[rear] = t;
        count++;
        return true;
    }

    bool dequeue() {
        if (count == 0) return false;
        front = (front + 1) % static_cast<int>(data.size());
        count--;
        return true;
    }

    bool remove(int id) {
        if (count == 0) return false;
        std::vector<Task> temp;
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % static_cast<int>(data.size());
            if (data[idx].id != id) temp.push_back(data[idx]);
        }
        if (static_cast<int>(temp.size()) == count) return false;
        front = 0;
        rear = -1;
        count = 0;
        for (const Task& t : temp) enqueue(t);
        return true;
    }

    bool update(const Task& t) {
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % static_cast<int>(data.size());
            if (data[idx].id == t.id) {
                data[idx] = t;
                return true;
            }
        }
        return false;
    }

    const Task* search(int id) const {
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % static_cast<int>(data.size());
            if (data[idx].id == id) return &data[idx];
        }
        return nullptr;
    }

    std::string display() const {
        if (count == 0) return "No tasks found";
        std::ostringstream os;
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % static_cast<int>(data.size());
            os << taskToString(data[idx]) << "\n";
        }
        return os.str();
    }
};

#endif
