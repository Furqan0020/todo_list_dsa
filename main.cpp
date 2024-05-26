#include <iostream>
#include <string>
using namespace std;

struct Task {
    std::string description;
    Task* next;
};

class TodoList {
private:
    Task* head;
    Task* undoStack;

public:
    TodoList() : head(nullptr), undoStack(nullptr) {}

    void addTask(const string& description) {
        Task* newTask = new Task{ description, head };
        head = newTask;
        newTask->next = undoStack;
        undoStack = newTask;
    }

    void undo() {
        if (undoStack) {
            Task* lastTask = undoStack;
            undoStack = undoStack->next;
            delete lastTask;
        }
    }

    void displayTasks() {
        Task* current = head;
        while (current) {
            std::cout << current->description << std::endl;
            current = current->next;
        }
    }

    ~TodoList() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TodoList todo;

    todo.addTask("Buy groceries");
    todo.addTask("Finish homework");
    todo.addTask("Call mom");

    cout << "Tasks in the to-do list:" << std::endl;
    todo.displayTasks();

    todo.undo();
    cout << "\nAfter undoing the last task:" << std::endl;
    todo.displayTasks();

    return 0;
}
