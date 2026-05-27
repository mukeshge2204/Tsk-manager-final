#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "array_tasks.h"
#include "avl_tree.h"
#include "circular_list.h"
#include "circular_queue.h"
#include "deque_tasks.h"
#include "doubly_list.h"
#include "queue_tasks.h"
#include "singly_list.h"
#include "stack_tasks.h"
#include "task.h"

std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) parts.push_back(token);
    return parts;
}

Task parseTaskFromParts(const std::vector<std::string>& p, int startIndex) {
    Task t;
    t.id = (startIndex < static_cast<int>(p.size()) && !p[startIndex].empty()) ? std::stoi(p[startIndex]) : 0;
    t.title = (startIndex + 1 < static_cast<int>(p.size())) ? p[startIndex + 1] : "";
    t.priority = (startIndex + 2 < static_cast<int>(p.size())) ? p[startIndex + 2] : "";
    t.status = (startIndex + 3 < static_cast<int>(p.size())) ? p[startIndex + 3] : "";
    t.deadline = (startIndex + 4 < static_cast<int>(p.size())) ? p[startIndex + 4] : "";
    return t;
}

int main(int argc, char* argv[]) {
    std::string inputPath = argc > 1 ? argv[1] : "../input.txt";
    std::string outputPath = argc > 2 ? argv[2] : "../output.txt";

    ArrayTasks arrayTasks;
    SinglyLinkedListTasks singly;
    DoublyLinkedListTasks doubly;
    CircularLinkedListTasks circular;
    StackTasks stack;
    QueueTasks queue;
    DequeTasks deque;
    CircularQueueTasks circularQueue(2000);
    AVLTreeTasks avl;

    std::ifstream fin(inputPath);
    if (!fin.is_open()) return 1;

    std::string line;
    std::string finalOutput = "No command executed";

    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = split(line, '|');
        if (parts.empty()) continue;

        if (parts[0] == "LOAD") {
            Task t = parseTaskFromParts(parts, 1);
            arrayTasks.add(t);
            singly.add(t);
            doubly.add(t);
            circular.add(t);
            stack.push(t);
            queue.enqueue(t);
            deque.pushBack(t);
            circularQueue.enqueue(t);
            avl.add(t);
            continue;
        }

        if (parts[0] != "COMMAND" || parts.size() < 4) continue;

        std::string structure = parts[1];
        std::string operation = parts[2];
        int id = parts[3].empty() ? 0 : std::stoi(parts[3]);
        Task t = parseTaskFromParts(parts, 3);

        auto outputSearch = [&](const Task* found) {
            finalOutput = found ? taskToString(*found) : "Task not found";
        };

        if (structure == "Array") {
            if (operation == "DISPLAY") finalOutput = arrayTasks.display();
            else if (operation == "SEARCH") outputSearch(arrayTasks.search(id));
            else if (operation == "DELETE") finalOutput = arrayTasks.remove(id) ? "Deleted" : "Task not found";
            else if (operation == "ADD") {
                arrayTasks.add(t);
                finalOutput = "Added";
            } else if (operation == "UPDATE") finalOutput = arrayTasks.update(t) ? "Updated" : "Task not found";
        } else if (structure == "SinglyLinkedList") {
            if (operation == "DISPLAY") finalOutput = singly.display();
            else if (operation == "SEARCH") outputSearch(singly.search(id));
            else if (operation == "DELETE") finalOutput = singly.remove(id) ? "Deleted" : "Task not found";
            else if (operation == "ADD") {
                singly.add(t);
                finalOutput = "Added";
            } else if (operation == "UPDATE") finalOutput = singly.update(t) ? "Updated" : "Task not found";
        } else if (structure == "DoublyLinkedList") {
            if (operation == "DISPLAY") finalOutput = doubly.display();
            else if (operation == "SEARCH") outputSearch(doubly.search(id));
            else if (operation == "DELETE") finalOutput = doubly.remove(id) ? "Deleted" : "Task not found";
            else if (operation == "ADD") {
                doubly.add(t);
                finalOutput = "Added";
            } else if (operation == "UPDATE") finalOutput = doubly.update(t) ? "Updated" : "Task not found";
        } else if (structure == "CircularLinkedList") {
            if (operation == "DISPLAY") finalOutput = circular.display();
            else if (operation == "SEARCH") outputSearch(circular.search(id));
            else if (operation == "DELETE") finalOutput = circular.remove(id) ? "Deleted" : "Task not found";
            else if (operation == "ADD") {
                circular.add(t);
                finalOutput = "Added";
            } else if (operation == "UPDATE") finalOutput = circular.update(t) ? "Updated" : "Task not found";
        } else if (structure == "Stack") {
            if (operation == "DISPLAY") finalOutput = stack.display();
            else if (operation == "SEARCH") outputSearch(stack.search(id));
            else if (operation == "DELETE") finalOutput = stack.remove(id) ? "Deleted" : "Task not found";
            else if (operation == "POP") finalOutput = stack.pop() ? "Popped" : "Stack empty";
            else if (operation == "ADD") {
                stack.push(t);
                finalOutput = "Added";
            } else if (operation == "UPDATE") finalOutput = stack.update(t) ? "Updated" : "Task not found";
        } else if (structure == "Queue") {
            if (operation == "DISPLAY") finalOutput = queue.display();
            else if (operation == "SEARCH") outputSearch(queue.search(id));
            else if (operation == "DELETE") finalOutput = queue.remove(id) ? "Deleted" : "Task not found";
            else if (operation == "DEQUEUE") finalOutput = queue.dequeue() ? "Dequeued" : "Queue empty";
            else if (operation == "ADD") {
                queue.enqueue(t);
                finalOutput = "Added";
            } else if (operation == "UPDATE") finalOutput = queue.update(t) ? "Updated" : "Task not found";
        } else if (structure == "Deque") {
            if (operation == "DISPLAY") finalOutput = deque.display();
            else if (operation == "SEARCH") outputSearch(deque.search(id));
            else if (operation == "DELETE") finalOutput = deque.remove(id) ? "Deleted" : "Task not found";
            else if (operation == "POP_FRONT") finalOutput = deque.popFront() ? "Front popped" : "Deque empty";
            else if (operation == "POP_BACK") finalOutput = deque.popBack() ? "Back popped" : "Deque empty";
            else if (operation == "ADD") {
                deque.pushBack(t);
                finalOutput = "Added";
            } else if (operation == "UPDATE") finalOutput = deque.update(t) ? "Updated" : "Task not found";
        } else if (structure == "CircularQueue") {
            if (operation == "DISPLAY") finalOutput = circularQueue.display();
            else if (operation == "SEARCH") outputSearch(circularQueue.search(id));
            else if (operation == "DELETE") finalOutput = circularQueue.remove(id) ? "Deleted" : "Task not found";
            else if (operation == "DEQUEUE") finalOutput = circularQueue.dequeue() ? "Dequeued" : "Queue empty";
            else if (operation == "ADD") finalOutput = circularQueue.enqueue(t) ? "Added" : "Circular queue full";
            else if (operation == "UPDATE") finalOutput = circularQueue.update(t) ? "Updated" : "Task not found";
        } else if (structure == "AVLTree") {
            if (operation == "DISPLAY") finalOutput = avl.display();
            else if (operation == "MORRIS") finalOutput = avl.morrisTraversal();
            else if (operation == "SEARCH") outputSearch(avl.search(id));
            else if (operation == "DELETE") finalOutput = avl.remove(id) ? "Deleted" : "Task not found";
            else if (operation == "ADD") {
                avl.add(t);
                finalOutput = "Added";
            } else if (operation == "UPDATE") finalOutput = avl.update(t) ? "Updated" : "Task not found";
        }
    }

    std::ofstream fout(outputPath);
    fout << finalOutput;
    return 0;
}
