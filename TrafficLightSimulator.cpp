#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <string>

// Enum representing the traffic light states
enum class LightState { RED, GREEN, YELLOW };

// Function to convert LightState enum to a readable string
std::string stateToString(LightState state) {
    switch (state) {
        case LightState::RED: return "RED";
        case LightState::GREEN: return "GREEN";
        case LightState::YELLOW: return "YELLOW";
        default: return "UNKNOWN";
    }
}

// TrafficLight class simulates a traffic light with state transitions
class TrafficLight {
public:
    // Constructor initializes name and starting state
    TrafficLight(const std::string& name)
        : name(name), currentState(LightState::RED), running(false) {}

    // Start the traffic light simulation in a separate thread
    void start() {
        running = true;
        worker = std::thread(&TrafficLight::run, this);
    }

    // Stop the simulation and wait for the thread to finish
    void stop() {
        running = false;
        if (worker.joinable()) worker.join();
    }

    // Destructor ensures the simulation thread is stopped
    ~TrafficLight() {
        stop();
    }

private:
    std::string name;              
    LightState currentState;      
    std::atomic<bool> running;     
    std::thread worker;            
    std::mutex mtx;               

    // Main loop that cycles through light states with delays
    void run() {
        while (running) {
            {
                // Lock output to avoid garbled prints if multithreaded
                std::lock_guard<std::mutex> lock(mtx);
                std::cout << "[" << name << "] Light is " << stateToString(currentState) << "\n";
            }

            // Wait for the duration of the current light, then switch state
            switch (currentState) {
                case LightState::RED:
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                    currentState = LightState::GREEN;
                    break;
                case LightState::GREEN:
                    std::this_thread::sleep_for(std::chrono::seconds(4));
                    currentState = LightState::YELLOW;
                    break;
                case LightState::YELLOW:
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    currentState = LightState::RED;
                    break;
            }
        }
    }
};

// Function to display the simple menu to user
void showMenu() {
    std::cout << "\n==== Traffic Light Simulation ====\n";
    std::cout << "1. Start Simulation\n";
    std::cout << "2. Stop Simulation\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose: ";
}

int main() {
    TrafficLight light("Main Street"); 
    bool isRunning = false;              
    
    // User interaction loop
    while (true) {
        showMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (!isRunning) {
                    light.start();      // Start simulation thread
                    isRunning = true;
                } else {
                    std::cout << "Simulation already running.\n";
                }
                break;
            case 2:
                if (isRunning) {
                    light.stop();       // Stop simulation thread
                    isRunning = false;
                } else {
                    std::cout << "Simulation not running.\n";
                }
                break;
            case 3:
                light.stop();           // Stop and exit
                return 0;
            default:
                std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
