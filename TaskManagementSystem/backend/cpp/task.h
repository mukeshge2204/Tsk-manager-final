#ifndef TASK_H
#define TASK_H

#include <sstream>
#include <string>

struct Task {
    int id = 0;
    std::string title;
    std::string priority;
    std::string status;
    std::string deadline;
};

inline std::string taskToString(const Task& t) {
    std::ostringstream os;
    os << "ID=" << t.id << ", Title=" << t.title << ", Priority=" << t.priority
       << ", Status=" << t.status << ", Deadline=" << t.deadline;
    return os.str();
}

#endif
