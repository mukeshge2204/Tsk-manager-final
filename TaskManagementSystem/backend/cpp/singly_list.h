#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <sstream>
#include <string>
#include "task.h"

struct SNode {
    Task data;
    SNode* next;
    explicit SNode(const Task& t) : data(t), next(nullptr) {}
};

class SinglyLinkedListTasks {
    SNode* head = nullptr;

   public:
    ~SinglyLinkedListTasks() {
        while (head) {
            SNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(const Task& t) {
        SNode* node = new SNode(t);
        if (!head) {
            head = node;
            return;
        }
        SNode* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }

    bool remove(int id) {
        if (!head) return false;
        if (head->data.id == id) {
            SNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        SNode* cur = head;
        while (cur->next && cur->next->data.id != id) cur = cur->next;
        if (!cur->next) return false;
        SNode* temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        return true;
    }

    bool update(const Task& t) {
        SNode* cur = head;
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
        SNode* cur = head;
        while (cur) {
            if (cur->data.id == id) return &cur->data;
            cur = cur->next;
        }
        return nullptr;
    }

    std::string display() const {
        if (!head) return "No tasks found";
        std::ostringstream os;
        SNode* cur = head;
        while (cur) {
            os << taskToString(cur->data) << "\n";
            cur = cur->next;
        }
        return os.str();
    }
};

#endif
