# To-Do Manager

This is a simple command-line to-do manager implemented in C++. It allows users to add, mark as completed, delete, view, undo, redo, and quit tasks.

## Usage

1. Compile the code using a C++ compiler.
2. Run the compiled executable.
3. Enter one of the following commands:
   - `add`: Add a new task to the to-do list.
   - `mark`: Mark a task as completed.
   - `delete`: Delete a task from the to-do list.
   - `view`: View tasks based on a filter (all/completed/pending).
   - `undo`: Undo the last action.
   - `redo`: Redo the last undone action.
   - `quit`: Exit the program.

## Task Format

Each task has the following properties:
- Description: A brief description of the task.
- Due Date: The due date of the task in the format dd/MM/yyyy.
- Completed: Indicates whether the task has been completed or not.

## Validations

- The due date must be in the format dd/MM/yyyy.
- Invalid commands and inputs will result in error messages.


