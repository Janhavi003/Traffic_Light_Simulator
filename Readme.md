# 🚦 Traffic Light Simulator (C++)

A console-based traffic light simulation system built in C++. It uses object-oriented design, threading, and state management to simulate a traffic light at an intersection.

---

## 📌 Features

- Simulates traffic light states: **RED**, **GREEN**, **YELLOW**
- Real-time transitions using C++ threads and timers
- CLI interface to start/stop the simulation
- Designed with `TrafficLight` class for modularity

---

## 🛠️ Technologies Used

- C++17
- `std::thread` and `std::chrono`
- Object-oriented programming
- Command-line interface

---

## 🚀 How to Run

### 🖥️ Prerequisites

- A C++ compiler like **g++**
- (Windows) MinGW or MSYS2 recommended
- (Mac/Linux) Preinstalled `g++` usually works
- Or use **Replit** or **Visual Studio**

---

### 🧪 Compile & Run (Command Line)

#### Windows (with `g++` installed):
```bash
g++ TrafficLightSimulator.cpp -o TrafficLightSimulator -pthread
.\TrafficLightSimulator.exe
