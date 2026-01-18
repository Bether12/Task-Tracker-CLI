# Task-Tracker-CLI

A robust Command Line Interface (CLI) application for task management, developed in C++. This project implements a full data lifecycle—from user input to JSON file persistence—without any external dependencies.

This project was designed to showcase fundamental Computer Science concepts applied to software engineering:

- **Memory Management & Pointers:** Implementation of entity lookup using pointers and pass-by-reference (&) to optimize Stack usage and prevent unnecessary deep copies.

- **Atomic Persistence:** Implementation of a "save-to-temp" strategy using a .temp file and the system's `rename()` function to guarantee data integrity and prevent file corruption during process failures.

- **Data Parsing:** Development of a custom manual parser for JSON files, utilizing pattern-matching algorithms and token trimming to transform raw text into typed objects.

## Technical Highlights

- **Algorithmic Robustness:** Exception handling `(std::invalid_argument, std::out_of_range)` to ensure the program remains stable even when encountering malformed input or corrupted IDs in the source file.

- **Timestamp Management:** Integrated use of the `<chrono>` library to capture and format precise timestamps in **YYYY-MM-DD HH:MM:SS** format.

- **Modular Architecture:** Strict separation of concerns between data definitions (Task), the persistence engine (Json), and business logic (task-cli).

## Project Structure

- **include/task.h:** Definition of the Task data structure.

- **include/jsonman.h & src/jsonman.cpp:** Engine responsible for data lifecycle (Load/Save) and string processing.

- **src/task-cli.cpp:** Program entry point and CLI user interface management.

## Compilation and Installation

To compile the project on Linux/Unix systems:

```bash
g++ -I./include src/task-cli.cpp src/jsonman.cpp -o task-cli
```

## Usage Guide

The Task CLI accepts 9 commands which define its functionality:

- Adding Tasks

    The `add` command creates a new task, sets its creation time, sets its status to "todo" and assigns it an unique ID, and has a **mandatory argument** which is the task description. If its the first time using the CLI, it will create the file data.json, where all the task will be stored. An usage example:

    ```bash
    ./task-cli add "Finish API project"
    #Output: Task added successfully (ID:1)
    ```

- Updating and Deleting Tasks

    The `update` command takes **2 mandatory arguments**, task ID and description, rewrites the description of the existing task with ID matching the provided one and set the time when it was updated. The `delete` command takes a **mandatory argument**, task ID, and deletes the task from data.json with ID matching the one provided. An usage example:  

    ```bash
    ./task-cli update 1 "Fix API project"
    ./task-cli delete 1
    ```

- Changing Task Status

    The `mark-in-progress` and `mark-done` commands have a **mandatory argument**, task ID, and change the status of the task with ID matching the ID provided to "in-progress" with the first command and to "done" with the later. An usage example:

    ```bash
    ./task-cli mark-in-progress 1
    ./task-cli mark-done 1
    ```

- Listing and Filtering Tasks

    The command `list` prints all the tasks in the data.json and has one optional parameter which works as a filter. The optional parameter can be `todo`, prints all the tasks with "todo" status, `in-progress`, prints all the tasks with "in-progress" status, and `done` prints all the tasks with "done" status. An usage example:

    ```bash
    ./task-cli list           # View all tasks
    ./task-cli list todo      # Filter by pending tasks
    ./task-cli list in-progress
    ./task-cli list done
    ```

## Design Decisions

As a CS student, I chose to develop a manual JSON parser instead of utilizing standard third-party libraries like `nlohmann/json`. The goal was to gain a deeper understanding of substring search logic and data structuring at a low level.