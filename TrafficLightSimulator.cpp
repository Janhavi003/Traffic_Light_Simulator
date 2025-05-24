#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <string>

enum class LightState { RED, GREEN, YELLOW };

std::string stateToString(LightState state) {
    switch (state) {
        case LightState::RED: return "RED";
        case LightState::GREEN: return "GREEN";
        case LightState::YELLOW: return "YELLOW";
        default: return "UNKNOWN";
    }
}

class TrafficLight {
public:
    TrafficLight(const std::string& name)
        : name(name), currentState(LightState::RED), running(false) {}

    void start() {
        running = true;
        worker = std::thread(&TrafficLight::run, this);
    }

    void stop() {
        running = false;
        if (worker.joinable()) worker.join();
    }

    ~TrafficLight() {
        stop();
    }

private:
    std::string name;
    LightState currentState;
    std::atomic<bool> running;
    std::thread worker;
    std::mutex mtx;

    void run() {
        while (running) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                std::cout << "[" << name << "] Light is " << stateToString(currentState) << "\n";
            }

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

    while (true) {
        showMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (!isRunning) {
                    light.start();
                    isRunning = true;
                } else {
                    std::cout << "Simulation already running.\n";
                }
                break;
            case 2:
                if (isRunning) {
                    light.stop();
                    isRunning = false;
                } else {
                    std::cout << "Simulation not running.\n";
                }
                break;
            case 3:
                light.stop();
                return 0;
            default:
                std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
