#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Task {
    int id;
    string description;
    Task* next;

    Task(int id, string desc) : id(id), description(desc), next(nullptr) {}
};
class ToDoList {
private:
    Task* head;
    int taskIdCounter;

    // Recursive function to print tasks
    void printTasks(Task* task) {
        if (task == nullptr) return;
        cout << "Task ID: " << task->id << ", Description: " << task->description << endl;
        printTasks(task->next);
    }

    // Recursive function to delete all tasks
    void clearTasks(Task* task) {
        if (task == nullptr) return;
        clearTasks(task->next);
        delete task;
    }

public:
    ToDoList() : head(nullptr), taskIdCounter(0) {}

    ~ToDoList() {
        clearTasks(head);
    }

    void addTask(const string& description) {
        Task* newTask = new Task(taskIdCounter++, description);
        newTask->next = head;
        head = newTask;
    }

    void removeTask(int id) {
        Task* temp = head;
        Task* prev = nullptr;
        while (temp != nullptr && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Task ID " << id << " not found." << endl;
            return;
        }
        if (prev == nullptr) {
            head = temp->next;
        }
        else {
            prev->next = temp->next;
        }
        delete temp;
    }

    void printTasks() {
        printTasks(head);
    }

    void clearTasks() {
        clearTasks(head);
        head = nullptr;
        taskIdCounter = 0;
    }
};
stack<Task*> undoStack;
queue<Task*> priorityQueue;

void undoLastAdd(ToDoList& list) {
    if (undoStack.empty()) {
        cout << "No tasks to undo." << endl;
        return;
    }
    Task* task = undoStack.top();
    undoStack.pop();
    list.removeTask(task->id);
    delete task;
}

void addPriorityTask(ToDoList& list, const string& description) {
    Task* newTask = new Task(-1, description); // -1 to indicate a priority task
    priorityQueue.push(newTask);
}

void processPriorityTasks(ToDoList& list) {
    while (!priorityQueue.empty()) {
        Task* task = priorityQueue.front();
        priorityQueue.pop();
        list.addTask(task->description);
        delete task;
    }
}
int main() {
    ToDoList todoList;

    todoList.addTask("Buy groceries");
    todoList.addTask("Complete C++ project");
    todoList.addTask("Call mom");

    undoStack.push(new Task(0, "Buy groceries"));
    undoStack.push(new Task(1, "Complete C++ project"));
    undoStack.push(new Task(2, "Call mom"));

    cout << "Current Tasks:" << endl;
    todoList.printTasks();

    cout << "\nRemoving Task ID 1:" << endl;
    todoList.removeTask(1);
    todoList.printTasks();

    cout << "\nUndo last add:" << endl;
    undoLastAdd(todoList);
    todoList.printTasks();

    cout << "\nAdding priority task:" << endl;
    addPriorityTask(todoList, "Urgent: Fix bug");
    processPriorityTasks(todoList);
    todoList.printTasks();

    cout << "\nClearing all tasks:" << endl;
    todoList.clearTasks();
    todoList.printTasks();
    system("pause");
    return 0;
}
