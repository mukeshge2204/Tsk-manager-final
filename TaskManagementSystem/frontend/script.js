const API_BASE = '/api';

async function loadTasks() {
  const res = await fetch(`${API_BASE}/tasks`);
  const tasks = await res.json();
  const tbody = document.querySelector('#taskTable tbody');
  tbody.innerHTML = '';

  tasks.forEach((task) => {
    const tr = document.createElement('tr');
    const idTd = document.createElement('td');
    idTd.textContent = task.id;
    const titleTd = document.createElement('td');
    titleTd.textContent = task.title;
    const priorityTd = document.createElement('td');
    priorityTd.textContent = task.priority;
    const statusTd = document.createElement('td');
    statusTd.textContent = task.status;
    const deadlineTd = document.createElement('td');
    deadlineTd.textContent = task.deadline;
    const actionsTd = document.createElement('td');

    const editBtn = document.createElement('button');
    editBtn.textContent = 'Edit';
    editBtn.addEventListener('click', () => editTask(task));

    const deleteBtn = document.createElement('button');
    deleteBtn.textContent = 'Delete';
    deleteBtn.addEventListener('click', () => deleteTask(task.id));

    actionsTd.appendChild(editBtn);
    actionsTd.appendChild(deleteBtn);

    tr.appendChild(idTd);
    tr.appendChild(titleTd);
    tr.appendChild(priorityTd);
    tr.appendChild(statusTd);
    tr.appendChild(deadlineTd);
    tr.appendChild(actionsTd);
    tbody.appendChild(tr);
  });
}

function getFormData() {
  return {
    title: document.getElementById('title').value,
    priority: document.getElementById('priority').value,
    status: document.getElementById('status').value,
    deadline: document.getElementById('deadline').value,
  };
}

document.getElementById('taskForm').addEventListener('submit', async (e) => {
  e.preventDefault();
  const taskId = document.getElementById('taskId').value;
  const method = taskId ? 'PUT' : 'POST';
  const url = taskId ? `${API_BASE}/tasks/${taskId}` : `${API_BASE}/tasks`;

  await fetch(url, {
    method,
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(getFormData()),
  });

  e.target.reset();
  document.getElementById('taskId').value = '';
  await loadTasks();
});

function editTask(task) {
  document.getElementById('taskId').value = task.id;
  document.getElementById('title').value = task.title;
  document.getElementById('priority').value = task.priority;
  document.getElementById('status').value = task.status;
  document.getElementById('deadline').value = task.deadline;
}

async function deleteTask(taskId) {
  await fetch(`${API_BASE}/tasks/${taskId}`, { method: 'DELETE' });
  await loadTasks();
}

async function runDsa(operation) {
  const structure = document.getElementById('structure').value;
  const taskId = document.getElementById('operationTaskId').value;
  const res = await fetch(`${API_BASE}/dsa`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ structure, operation, id: taskId ? Number(taskId) : null }),
  });
  const result = await res.json();
  document.getElementById('dsaOutput').textContent = result.output || result.error || 'No response';
}

loadTasks();
