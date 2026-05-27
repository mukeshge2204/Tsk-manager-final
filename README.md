# Task Management System

A complete beginner-friendly **Task Management System** using:
- Frontend: HTML, CSS, JavaScript
- Backend: Python Flask + REST API
- Database: SQLite
- DSA Engine: C++ (invoked by Flask through subprocess)

## Folder Structure

```text
TaskManagementSystem/
├── frontend/
│   ├── index.html
│   ├── style.css
│   └── script.js
├── backend/
│   ├── app.py
│   ├── tasks.db (auto-created)
│   ├── input.txt
│   ├── output.txt
│   └── cpp/
│       ├── main.cpp
│       ├── task.h
│       ├── array_tasks.h
│       ├── singly_list.h
│       ├── doubly_list.h
│       ├── circular_list.h
│       ├── stack_tasks.h
│       ├── queue_tasks.h
│       ├── deque_tasks.h
│       ├── circular_queue.h
│       └── avl_tree.h
```

## Setup Steps (Windows)

1. Open terminal in repository root.
2. Install Python dependency:
   ```bash
   pip install flask
   ```
3. Compile C++:
   ```bash
   cd TaskManagementSystem/backend/cpp
   g++ main.cpp -o task_dsa.exe
   ```
4. Run Flask server:
   ```bash
   cd ..
   python app.py
   ```
5. Open browser:
   - `http://127.0.0.1:5000`

## Setup Steps (Linux/macOS)

```bash
python -m pip install flask
cd TaskManagementSystem/backend/cpp
g++ main.cpp -o task_dsa
cd ..
python app.py
```

## REST API Endpoints

- `GET /api/tasks` → display all tasks
- `POST /api/tasks` → add task
- `GET /api/tasks/<id>` → search task by id
- `PUT /api/tasks/<id>` → update task
- `DELETE /api/tasks/<id>` → delete task
- `POST /api/dsa` → run DSA command through C++

### Example Task JSON

```json
{
  "title": "Finish report",
  "priority": "High",
  "status": "Pending",
  "deadline": "2026-12-31"
}
```

### DSA API Example

`POST /api/dsa`

```json
{
  "structure": "AVLTree",
  "operation": "MORRIS",
  "id": null
}
```

### Sample Output

```text
ID=1, Title=Finish report, Priority=High, Status=Pending, Deadline=2026-12-31
ID=2, Title=Prepare slides, Priority=Medium, Status=Done, Deadline=2026-10-01
```

## How LOAD Works

Before every DSA API execution, Flask writes all tasks from SQLite to `input.txt` in `LOAD` format.
Then it writes one `COMMAND` line.
C++ rebuilds all requested structures from LOAD commands, runs the command, and writes final output to `output.txt`.
