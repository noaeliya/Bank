# ThreadSafe-Bank-Simulator

A multi-threaded banking simulation system developed in **Modern C++ (C++17)**.

##  Core Features
* **Thread-Safety:** Uses `std::mutex` and `std::lock_guard` to prevent race conditions during concurrent account operations.
* **Modern C++ Memory Management:** Employs Smart Pointers (`std::shared_ptr`) and STL Containers (`std::vector`) with zero manual `new`/`delete` allocations.
* **Concurrency Test:** Simulates multiple worker threads (e.g., ATM and Mobile App) modifying a shared balance simultaneously to verify data integrity.

##  How to Build and Run

Run the following command from the project root directory:

```bash
g++ -std=c++17 -Iheaders main.cpp Account.cpp Bank.cpp Person.cpp Transaction.cpp -o bank_simulation.exe
.\bank_simulation.exe
