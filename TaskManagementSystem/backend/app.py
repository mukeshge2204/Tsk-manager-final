import os
import sqlite3
import subprocess
import sys
from pathlib import Path

from flask import Flask, jsonify, request, send_from_directory

BASE_DIR = Path(__file__).resolve().parent
FRONTEND_DIR = BASE_DIR.parent / "frontend"
DB_PATH = BASE_DIR / "tasks.db"
INPUT_PATH = BASE_DIR / "input.txt"
OUTPUT_PATH = BASE_DIR / "output.txt"
CPP_DIR = BASE_DIR / "cpp"
CPP_EXE = CPP_DIR / ("task_dsa.exe" if os.name == "nt" else "task_dsa")

app = Flask(__name__, static_folder=str(FRONTEND_DIR), static_url_path="")


def get_conn():
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn


def init_db():
    with get_conn() as conn:
        conn.execute(
            """
            CREATE TABLE IF NOT EXISTS tasks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                priority TEXT NOT NULL,
                status TEXT NOT NULL,
                deadline TEXT NOT NULL
            )
            """
        )


def get_all_tasks():
    with get_conn() as conn:
        rows = conn.execute("SELECT * FROM tasks ORDER BY id").fetchall()
        return [dict(row) for row in rows]


def write_commands_for_cpp(structure, operation, payload):
    def safe_field(value):
        # Keep input format predictable for the C++ parser.
        return str(value).replace("|", " ").replace("\n", " ").replace("\r", " ")

    tasks = get_all_tasks()
    lines = []

    for task in tasks:
        lines.append(
            f"LOAD|{task['id']}|{safe_field(task['title'])}|{safe_field(task['priority'])}|{safe_field(task['status'])}|{safe_field(task['deadline'])}"
        )

    task_id = payload.get("id") if payload else ""
    title = payload.get("title", "") if payload else ""
    priority = payload.get("priority", "") if payload else ""
    status = payload.get("status", "") if payload else ""
    deadline = payload.get("deadline", "") if payload else ""

    lines.append(
        f"COMMAND|{safe_field(structure)}|{safe_field(operation)}|{task_id if task_id is not None else ''}|{safe_field(title)}|{safe_field(priority)}|{safe_field(status)}|{safe_field(deadline)}"
    )

    INPUT_PATH.write_text("\n".join(lines), encoding="utf-8")


def run_cpp_program():
    if not CPP_EXE.exists():
        return {
            "error": "C++ executable not found. Compile backend/cpp/main.cpp first."
        }, 400

    try:
        result = subprocess.run(
            [str(CPP_EXE), str(INPUT_PATH), str(OUTPUT_PATH)],
            check=False,
            capture_output=True,
            text=True,
            cwd=str(CPP_DIR),
        )
        if result.returncode != 0:
            print(result.stderr, file=sys.stderr)
            return {
                "error": "C++ program failed. Check server logs.",
            }, 500
        output_text = OUTPUT_PATH.read_text(encoding="utf-8") if OUTPUT_PATH.exists() else ""
        return {"output": output_text.strip()}, 200
    except Exception as ex:  # beginner-friendly single fallback
        print(str(ex), file=sys.stderr)
        return {"error": "Internal server error"}, 500


@app.route("/")
def home():
    return send_from_directory(FRONTEND_DIR, "index.html")


@app.route("/api/tasks", methods=["GET"])
def list_tasks():
    return jsonify(get_all_tasks())


@app.route("/api/tasks", methods=["POST"])
def add_task():
    data = request.get_json(force=True)
    with get_conn() as conn:
        cur = conn.execute(
            "INSERT INTO tasks (title, priority, status, deadline) VALUES (?, ?, ?, ?)",
            (data["title"], data["priority"], data["status"], data["deadline"]),
        )
        task_id = cur.lastrowid
    return jsonify({"message": "Task added", "id": task_id}), 201


@app.route("/api/tasks/<int:task_id>", methods=["GET"])
def get_task(task_id):
    with get_conn() as conn:
        row = conn.execute("SELECT * FROM tasks WHERE id = ?", (task_id,)).fetchone()
    if row is None:
        return jsonify({"error": "Task not found"}), 404
    return jsonify(dict(row))


@app.route("/api/tasks/<int:task_id>", methods=["PUT"])
def update_task(task_id):
    data = request.get_json(force=True)
    with get_conn() as conn:
        cur = conn.execute(
            "UPDATE tasks SET title=?, priority=?, status=?, deadline=? WHERE id=?",
            (data["title"], data["priority"], data["status"], data["deadline"], task_id),
        )
    if cur.rowcount == 0:
        return jsonify({"error": "Task not found"}), 404
    return jsonify({"message": "Task updated"})


@app.route("/api/tasks/<int:task_id>", methods=["DELETE"])
def delete_task(task_id):
    with get_conn() as conn:
        cur = conn.execute("DELETE FROM tasks WHERE id = ?", (task_id,))
    if cur.rowcount == 0:
        return jsonify({"error": "Task not found"}), 404
    return jsonify({"message": "Task deleted"})


@app.route("/api/dsa", methods=["POST"])
def dsa_operation():
    data = request.get_json(force=True)
    structure = data.get("structure", "Array")
    operation = data.get("operation", "DISPLAY")

    write_commands_for_cpp(structure, operation, data)
    result, code = run_cpp_program()
    return jsonify(result), code


if __name__ == "__main__":
    init_db()
    # host 0.0.0.0 for easy local browser testing
    app.run(debug=False, host="0.0.0.0", port=5000)
