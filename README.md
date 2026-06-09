# ThreadSafe-Bank-Simulator

A high-performance, multi-threaded banking simulation system developed in **Modern C++ (C++17)**. This project demonstrates industry-standard practices in software engineering, focusing on concurrent programming, object-oriented design (OOP), automated memory management, and robust error prevention.

The simulator models a real-world banking ecosystem where multiple concurrent entities (e.g., automated teller machines, mobile applications, and web services) manipulate shared account resources simultaneously without compromising data integrity.

---

## Key Features

* **Thread-Safe Operations:** Implements fine-grained synchronization mechanisms using `std::mutex` and `std::lock_guard` to shield account balances and transaction logs from data races and concurrent write corruption.
* **Modern C++ Memory Management:** Strictly follows the **Rule of Zero** and **RAII** principles. Standard Library containers (`std::vector`, `std::string`) and Smart Pointers (`std::shared_ptr`) are utilized to eliminate raw pointers (`new`/`delete`), ensuring absolute immunity to memory leaks and dangling pointers.
* **Concurrent Simulation Engine:** Includes a pre-configured stress-test scenario in `main.cpp` where multiple worker threads execute thousands of concurrent banking operations on a single shared account to validate structural race-condition resistance.
* **Standard Build System:** Structured and ready for cross-platform deployment using **CMake**, facilitating clean compilations across different development environments.

---

##  System Architecture

The project consists of decoupled components built around modern object relations:

* **`Bank`**: Manages a collection of secure bank accounts using thread-safe vectors, tracks the global asset reserves, and handles top-level operations like adding/removing accounts and clients.
* **`Account`**: Represents a standalone financial account containing a balanced ledger, user access definitions, and dedicated mutex locks protecting internal state transitions.
* **`Person`**: Models client data natively utilizing standard strings for optimal memory layout and execution safety.
* **`Transaction`**: A immutable record tracking historical capital flows between origin and destination nodes.

---

##  How to Build and Run

### Prerequisites
* A C++ compiler supporting **C++17** or higher (e.g., GCC 7+, Clang 5+, or MSVC 2017+).
* **CMake** (version 3.15 or higher).

### Compilation via CMake (Recommended)
1. Navigate to the root directory of the project:
   ```bash
   cd /path/to/ThreadSafe-Bank-Simulator
