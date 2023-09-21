#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <regex>

class Task {
public:
    std::string description;
    std::string dueDate;
    bool completed;

    Task(std::string desc, std::string due) : description(desc), dueDate(due), completed(false) {}

    void markCompleted() {
        this->completed = true;
    }
};

class TaskBuilder {
public:
    std::string description;
    std::string dueDate;

    TaskBuilder& setDescription(std::string desc) {
        this->description = desc;
        return *this;
    }

    TaskBuilder& setDueDate(std::string due) {
        this->dueDate = due;
        return *this;
    }

    Task* build() {
        return new Task(description, dueDate);
    }
};

class Memento {
public:
    std::map<std::string, Task*> state;

    Memento(std::map<std::string, Task*> s) : state(s) {}
};

class ToDoList {
private:
    std::map<std::string, Task*> tasks;
    std::vector<Memento*> history;
    int current;

public:
    ToDoList() : current(-1) {}

    void addTask(Task* task) {
        tasks[task->description] = task;
        saveState();
    }

    void markCompleted(std::string desc) {
        if (tasks.count(desc)) {
            tasks[desc]->markCompleted();
            saveState();
        } else {
            throw std::invalid_argument("Task not found.");
        }
    }

    void deleteTask(std::string desc) {
        if (tasks.count(desc)) {
            tasks.erase(desc);
            saveState();
        }
    }

    void viewTasks(std::string filter = "all") {
        if (tasks.empty()) {
            throw std::runtime_error("No tasks to view.");
        }
        if (filter != "all" && filter != "completed" && filter != "pending") {
            throw std::invalid_argument("Invalid filter. Please enter 'all', 'completed', or 'pending'.");
        }

        bool taskFound = false;
        for (auto& task : tasks) {
            if (filter == "all" || (filter == "completed" && task.second->completed) || (filter == "pending" && !task.second->completed)) {
                std::cout << task.second->description << " - " << (task.second->completed ? "Completed" : "Pending") << ", Due: " << task.second->dueDate << std::endl;
                taskFound = true;
            }
        }

        if (!taskFound) {
            throw std::runtime_error("No tasks found for the given filter.");
        }
    }

    void undo() {
        if (current > 0) {
            current--;
            tasks = history[current]->state;
        } else {
            throw std::runtime_error("Nothing to undo.");
        }
    }

    void redo() {
        if (current < history.size() - 1) {
            current++;
            tasks = history[current]->state;
        } else {
            throw std::runtime_error("Nothing to redo.");
        }
    }

private:
    void saveState() {
        while (history.size() > current + 1) {
            history.pop_back();
        }
        history.push_back(new Memento(tasks));
        current++;
    }
};

bool isValidDate(const std::string& date) {
    std::regex datePattern("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/([12][0-9]{3})");
    return std::regex_match(date, datePattern);
}

int main() {
    ToDoList toDoList;
    std::string command;

    while (true) {
        std::cout << "Enter command (add/mark/delete/view/undo/redo/quit): ";
        std::cin >> command;

        try {
            if (command == "add") {
                std::string desc, due;
                std::cout << "Enter description: ";
                std::cin.ignore();
                std::getline(std::cin, desc);
                std::cout << "Enter due date (dd/MM/yyyy): ";
                std::cin >> due;

                if (!isValidDate(due)) {
                    std::cout << "Invalid due date. Please enter a date in the format dd/MM/yyyy." << std::endl;
                    continue;
                }

                TaskBuilder builder;
                toDoList.addTask(builder.setDescription(desc).setDueDate(due).build());
            } else if (command == "mark") {
                std::string desc;
                std::cout << "Enter description: ";
                std::cin.ignore();
                std::getline(std::cin, desc);
                toDoList.markCompleted(desc);
            } else if (command == "delete") {
                std::string desc;
                std::cout << "Enter description: ";
                std::cin.ignore();
                std::getline(std::cin, desc);
                toDoList.deleteTask(desc);
            } else if (command == "view") {
                std::string filter;
                std::cout << "Enter filter (all/completed/pending): ";
                std::cin >> filter;
                toDoList.viewTasks(filter);
            } else if (command == "undo") {
                toDoList.undo();
            } else if (command == "redo") {
                toDoList.redo();
            } else if (command == "quit") {
                break;
            } else {
                std::cout << "Invalid command." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}