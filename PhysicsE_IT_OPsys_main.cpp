#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <map>

//Created Idea: 2023
//Initially it was only a physics concept, but in 2025,
//I wanted to combine the other topics into a real-life scenario
//Implemented Physics concepts: 2023
//Updated code for IT and Operating Systems Concepts into it: 2025
// I may modify other codes here later.

/*
Topic: Energy Home Management (light bulbs, usage of electricity, etc).
In this system, this project will simulate how devices like light 
bulbs, air conditioners, and security cameras consume power and
how the system manages this data/information.
In other words, it simulates a smart home automation system, 
involving the calculation of energy consumption by various devices, 
sending this data over a network, and managing these devices through
a simulated operating system. It uses Physics (energy consumption), 
IT concepts (networking, hardware management), 
and Operating Systems (process management) for this case.
*/

//Updated comments: 2025

// Constants for physics calculation
const double GRAVITY = 9.81;  // m/s^2 (not used directly but could be extended for additional physics)

// Function to calculate energy consumption of a device (Energy = Power * Time)
double calculateEnergyConsumption(double power, double time) {
    return power * time;  // Energy (in watt-hours)
}

// Simulate Networking (sending and receiving data between devices and central hub)
class Network {
public:
    void sendData(const std::string& message) {
        std::cout << "Sending data: " << message << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate network delay
        std::cout << "Data sent successfully.\n";
    }

    void receiveData() {
        std::cout << "Receiving data...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate network delay
        std::cout << "Data received: Smart home energy status.\n";
    }
};

// Simulate Hardware Management (CPU and memory usage)
class Hardware {
public:
    void allocateMemory(int sizeInKB) {
        std::cout << "Allocating " << sizeInKB << " KB of memory...\n";
        memoryAllocated += sizeInKB;
        std::cout << "Memory allocated successfully. Total memory used: " << memoryAllocated << " KB.\n";
    }

    void releaseMemory(int sizeInKB) {
        if (memoryAllocated >= sizeInKB) {
            memoryAllocated -= sizeInKB;
            std::cout << "Released " << sizeInKB << " KB of memory. Total memory used: " << memoryAllocated << " KB.\n";
        } else {
            std::cout << "Error: Not enough memory to release.\n";
        }
    }

    void simulateCPUUsage() {
        std::cout << "Simulating CPU usage for 2 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate CPU usage
        std::cout << "CPU usage simulation complete.\n";
    }

private:
    int memoryAllocated = 0;
};

// Simulate Process Management in an Operating System
class Process {
public:
    Process(std::string name, int pid) : name(name), pid(pid) {
        memory = new char[1024]; // Simulate memory allocation (1KB)
        std::cout << "Process " << name << " with PID " << pid << " created.\n";
    }

    ~Process() {
        delete[] memory; // Free memory when process ends
        std::cout << "Process " << name << " with PID " << pid << " terminated.\n";
    }

    int getPid() const { return pid; }

    std::string getName() const { return name; }

private:
    std::string name;
    int pid;
    char* memory; // Simulated memory space
};

// Simulate Operating System's Process Management
class OS {
public:
    void createProcess(const std::string& name) {
        int pid = nextPid++;
        Process* p = new Process(name, pid);
        processes.push_back(p);
    }

    void terminateProcess(int pid) {
        for (auto it = processes.begin(); it != processes.end(); ++it) {
            if ((*it)->getPid() == pid) {
                delete *it;
                processes.erase(it);
                std::cout << "Process with PID " << pid << " terminated.\n";
                return;
            }
        }
        std::cout << "Process with PID " << pid << " not found.\n";
    }

    void showProcesses() {
        std::cout << "Current Processes:\n";
        for (auto& p : processes) {
            std::cout << "Process: " << p->getName() << " PID: " << p->getPid() << "\n";
        }
    }

private:
    std::vector<Process*> processes;
    int nextPid = 1;
};

// Simulate Devices (Light Bulb, AC, Camera)
class SmartDevice {
public:
    SmartDevice(std::string name, double powerRating) : name(name), powerRating(powerRating), isOn(false) {}

    void turnOn() {
        isOn = true;
        std::cout << name << " is now ON.\n";
    }

    void turnOff() {
        isOn = false;
        std::cout << name << " is now OFF.\n";
    }

    void simulateDeviceUsage(double time) {
        if (isOn) {
            double energyUsed = calculateEnergyConsumption(powerRating, time);
            std::cout << name << " used " << energyUsed << " Wh in " << time << " hours.\n";
            energyConsumed += energyUsed;
        }
    }

    double getEnergyConsumed() const {
        return energyConsumed;
    }

private:
    std::string name;
    double powerRating;  // Power rating in watts
    bool isOn;
    double energyConsumed = 0;
};

// Smart Home System to manage devices and network communication
class SmartHome {
public:
    void addDevice(const std::string& name, double powerRating) {
        devices.push_back(SmartDevice(name, powerRating));
    }

    void manageDevices() {
        for (auto& device : devices) {
            device.turnOn();
            device.simulateDeviceUsage(2);  // Simulate 2 hours of usage
            device.turnOff();
        }
    }

    void sendEnergyDataToHub(Network& network) {
        double totalEnergy = 0;
        for (auto& device : devices) {
            totalEnergy += device.getEnergyConsumed();
        }
        std::string message = "Total energy consumed by devices: " + std::to_string(totalEnergy) + " Wh";
        network.sendData(message);
    }

private:
    std::vector<SmartDevice> devices;
};

int main() {
    // Part 1: Physics - Calculate energy consumption of smart devices
    double power = 60.0; // Power in watts (for example, a light bulb)
    double time = 2.0;   // Time in hours

    double energy = calculateEnergyConsumption(power, time);
    std::cout << "Energy consumed by the light bulb: " << energy << " Wh\n";

    // Part 2: IT - Simulate Networking: Sending energy data to central hub
    Network network;
    network.sendData("Energy data: " + std::to_string(energy));
    network.receiveData();

    // Part 3: IT - Hardware Management: Simulate CPU and memory usage for device management
    Hardware hardware;
    hardware.allocateMemory(1024);  // Allocate memory for 1 device
    hardware.simulateCPUUsage();    // Simulate CPU usage for managing devices
    hardware.releaseMemory(1024);   // Release memory

    // Part 4: Operating Systems - Simulate Process Management for smart home devices
    OS os;
    os.createProcess("Smart Home Device Management Process");

    // Create a Smart Home system
    SmartHome home;
    home.addDevice("Light Bulb", 60.0);  // Light bulb with 60 watts power rating
    home.addDevice("Air Conditioner", 1500.0); // AC with 1500 watts power rating
    home.addDevice("Security Camera", 10.0);  // Security camera with 10 watts power rating

    // Simulate managing the devices
    home.manageDevices();

    // Send energy consumption data to a central hub
    home.sendEnergyDataToHub(network);

    // Show processes
    os.showProcesses();

    // Terminate process
    os.terminateProcess(1);

    return 0;
}
