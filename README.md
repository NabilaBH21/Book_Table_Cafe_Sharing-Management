# Book & Table Sharing Café Simulation

A concurrent **Book & Table Sharing Café Simulation** developed in C to demonstrate operating system concepts such as **process management, semaphores, mutex locks, synchronization, and race-condition prevention**.

## 📌 Project Overview

The simulation represents a real-world café where:

* A limited number of tables are available.
* Customers can borrow books while seated.
* Multiple customers arrive and interact concurrently.
* Customers wait when all tables are occupied.
* Books can be borrowed and returned safely.
* Shared resource status remains synchronized.

## 🛠️ Technologies & Concepts

* **C Programming**
* POSIX Threads (`pthread`)
* POSIX Semaphores
* Mutex Locks
* Process Management
* `fork()`
* `waitpid()`
* Critical Sections
* Process Synchronization
* Race Condition Prevention

## ⚙️ Main Features

### Table Management

A semaphore controls access to the limited number of café tables. Customers wait when no table is available and release the table after leaving.

### Book Management

The program searches for an available book and marks it as borrowed. Mutex locking prevents multiple customers from modifying book information simultaneously.

When a customer returns a book, the mutex is also used to safely update its status.

### Customer Simulation

Each customer process simulates a café visit:

1. Wait for an available table.
2. Enter the café.
3. Borrow an available book.
4. Read for a simulated period.
5. Return the book.
6. Leave the café.
7. Release the table.

The reading period is simulated using a random sleep of approximately **1–5 seconds**.

## 🔐 Synchronization

The project uses:

### Semaphore

A semaphore controls the number of customers who can occupy tables at the same time.

```text
sem_wait()
    ↓
Acquire available table
    ↓
Customer uses table
    ↓
sem_post()
    ↓
Release table
```

### Mutex

Mutex locks protect shared book inventory from simultaneous access and help prevent race conditions.

## 🔄 Process Management

The main process:

1. Initializes the table semaphore.
2. Initializes the book mutex.
3. Creates customer processes using `fork()`.
4. Each child executes the customer simulation.
5. The parent waits for all child processes using `waitpid()`.

## 📊 Simulation Configuration

The demonstrated simulation uses:

* **10 Customers**
* **5 Books**
* **3 Tables**

## ▶️ How to Run

### Linux / Ubuntu / WSL

Compile the program:

```bash
gcc cafe_simulation.c -o cafe_simulation -pthread
```

Run:

```bash
./cafe_simulation
```

> The project uses POSIX process/thread synchronization concepts, so Linux, Ubuntu, or WSL is recommended.

## 📂 Project Structure

```text
book-table-sharing-cafe-simulation/
│
├── cafe_simulation.c
├── README.md
└── CSE-325-presentation.pptx
```

## 🎯 Learning Outcomes

This project provides practical experience with:

* Process creation and management
* Semaphores
* Mutex locks
* Shared-resource synchronization
* Race-condition prevention
* Concurrent programming
* Critical sections
* Resource allocation

It also demonstrates how concurrency problems such as **race conditions, deadlocks, and resource starvation** can occur and how synchronization strategies can help prevent them.

## 👥 Project

**Course:** CSE-325
**Project:** Book & Table Sharing Café Simulation

### Contributors

* Abu Sufian — 2023-3-60-149
* Nabila Binti Hossain — 2023-3-60-242

## 📄 Presentation

The project presentation explains the café scenario, synchronization objectives, implementation, process management, and simulation output.

## 📜 License

This project was developed for academic and educational purposes.
