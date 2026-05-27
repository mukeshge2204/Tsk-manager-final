#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <sstream>
#include <string>
#include "task.h"

struct CNode {
    Task data;
    CNode* next;
    explicit CNode(const Task& t) : data(t), next(nullptr) {}
};

class CircularLinkedListTasks {
    CNode* tail = nullptr;

   public:
    ~CircularLinkedListTasks() {
        if (!tail) return;
        CNode* head = tail->next;
        tail->next = nullptr;
        while (head) {
            CNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(const Task& t) {
        CNode* node = new CNode(t);
        if (!tail) {
            tail = node;
            tail->next = tail;
            return;
        }
        node->next = tail->next;
        tail->next = node;
        tail = node;
    }

    bool remove(int id) {
        if (!tail) return false;
        CNode* prev = tail;
        CNode* cur = tail->next;
        do {
            if (cur->data.id == id) {
                if (cur == prev) {
                    delete cur;
                    tail = nullptr;
                } else {
                    prev->next = cur->next;
                    if (cur == tail) tail = prev;
                    delete cur;
                }
                return true;
            }
            prev = cur;
            cur = cur->next;
        } while (cur != tail->next);
        return false;
    }

    bool update(const Task& t) {
        if (!tail) return false;
        CNode* cur = tail->next;
        do {
            if (cur->data.id == t.id) {
                cur->data = t;
                return true;
            }
            cur = cur->next;
        } while (cur != tail->next);
        return false;
    }

    const Task* search(int id) const {
        if (!tail) return nullptr;
        CNode* cur = tail->next;
        do {
            if (cur->data.id == id) return &cur->data;
            cur = cur->next;
        } while (cur != tail->next);
        return nullptr;
    }

    std::string display() const {
        if (!tail) return "No tasks found";
        std::ostringstream os;
        CNode* cur = tail->next;
        do {
            os << taskToString(cur->data) << "\n";
            cur = cur->next;
        } while (cur != tail->next);
        return os.str();
    }
};

#endif
