#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <sstream>
#include <string>
#include "task.h"

struct DNode {
    Task data;
    DNode* prev;
    DNode* next;
    explicit DNode(const Task& t) : data(t), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedListTasks {
    DNode* head = nullptr;
    DNode* tail = nullptr;

   public:
    ~DoublyLinkedListTasks() {
        while (head) {
            DNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(const Task& t) {
        DNode* node = new DNode(t);
        if (!head) {
            head = tail = node;
            return;
        }
        tail->next = node;
        node->prev = tail;
        tail = node;
    }

    bool remove(int id) {
        DNode* cur = head;
        while (cur && cur->data.id != id) cur = cur->next;
        if (!cur) return false;
        if (cur->prev) cur->prev->next = cur->next;
        else head = cur->next;
        if (cur->next) cur->next->prev = cur->prev;
        else tail = cur->prev;
        delete cur;
        return true;
    }

    bool update(const Task& t) {
        DNode* cur = head;
        while (cur) {
            if (cur->data.id == t.id) {
                cur->data = t;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    const Task* search(int id) const {
        DNode* cur = head;
        while (cur) {
            if (cur->data.id == id) return &cur->data;
            cur = cur->next;
        }
        return nullptr;
    }

    std::string display() const {
        if (!head) return "No tasks found";
        std::ostringstream os;
        DNode* cur = head;
        while (cur) {
            os << taskToString(cur->data) << "\n";
            cur = cur->next;
        }
        return os.str();
    }
};

#endif
