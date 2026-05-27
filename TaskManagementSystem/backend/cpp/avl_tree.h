#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <sstream>
#include <string>
#include "task.h"

struct AVLNode {
    Task data;
    AVLNode* left;
    AVLNode* right;
    int height;
    explicit AVLNode(const Task& t) : data(t), left(nullptr), right(nullptr), height(1) {}
};

class AVLTreeTasks {
    AVLNode* root = nullptr;

    int h(AVLNode* n) const { return n ? n->height : 0; }

    int balance(AVLNode* n) const { return n ? h(n->left) - h(n->right) : 0; }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* t2 = x->right;
        x->right = y;
        y->left = t2;
        y->height = 1 + std::max(h(y->left), h(y->right));
        x->height = 1 + std::max(h(x->left), h(x->right));
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* t2 = y->left;
        y->left = x;
        x->right = t2;
        x->height = 1 + std::max(h(x->left), h(x->right));
        y->height = 1 + std::max(h(y->left), h(y->right));
        return y;
    }

    AVLNode* insertNode(AVLNode* node, const Task& t) {
        if (!node) return new AVLNode(t);
        if (t.id < node->data.id)
            node->left = insertNode(node->left, t);
        else if (t.id > node->data.id)
            node->right = insertNode(node->right, t);
        else {
            node->data = t;
            return node;
        }

        node->height = 1 + std::max(h(node->left), h(node->right));
        int b = balance(node);

        if (b > 1 && t.id < node->left->data.id) return rightRotate(node);
        if (b < -1 && t.id > node->right->data.id) return leftRotate(node);
        if (b > 1 && t.id > node->left->data.id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (b < -1 && t.id < node->right->data.id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* cur = node;
        while (cur->left) cur = cur->left;
        return cur;
    }

    AVLNode* deleteNode(AVLNode* node, int id) {
        if (!node) return node;

        if (id < node->data.id)
            node->left = deleteNode(node->left, id);
        else if (id > node->data.id)
            node->right = deleteNode(node->right, id);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLNode* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data.id);
            }
        }

        if (!node) return node;

        node->height = 1 + std::max(h(node->left), h(node->right));
        int b = balance(node);

        if (b > 1 && balance(node->left) >= 0) return rightRotate(node);
        if (b > 1 && balance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (b < -1 && balance(node->right) <= 0) return leftRotate(node);
        if (b < -1 && balance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* searchNode(AVLNode* node, int id) const {
        if (!node || node->data.id == id) return node;
        if (id < node->data.id) return searchNode(node->left, id);
        return searchNode(node->right, id);
    }

    void inorder(AVLNode* node, std::ostringstream& os) const {
        if (!node) return;
        inorder(node->left, os);
        os << taskToString(node->data) << "\n";
        inorder(node->right, os);
    }

    void clear(AVLNode* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

   public:
    ~AVLTreeTasks() { clear(root); }

    void add(const Task& t) { root = insertNode(root, t); }

    bool remove(int id) {
        if (!searchNode(root, id)) return false;
        root = deleteNode(root, id);
        return true;
    }

    bool update(const Task& t) {
        if (!searchNode(root, t.id)) return false;
        root = deleteNode(root, t.id);
        root = insertNode(root, t);
        return true;
    }

    const Task* search(int id) const {
        AVLNode* found = searchNode(root, id);
        return found ? &found->data : nullptr;
    }

    std::string display() const {
        std::ostringstream os;
        inorder(root, os);
        std::string out = os.str();
        return out.empty() ? "No tasks found" : out;
    }

    std::string morrisTraversal() const {
        if (!root) return "No tasks found";
        std::ostringstream os;
        AVLNode* current = root;
        while (current) {
            if (!current->left) {
                os << taskToString(current->data) << "\n";
                current = current->right;
            } else {
                AVLNode* predecessor = current->left;
                while (predecessor->right && predecessor->right != current) {
                    predecessor = predecessor->right;
                }
                if (!predecessor->right) {
                    predecessor->right = current;
                    current = current->left;
                } else {
                    predecessor->right = nullptr;
                    os << taskToString(current->data) << "\n";
                    current = current->right;
                }
            }
        }
        return os.str();
    }
};

#endif
