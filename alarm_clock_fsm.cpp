#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <stdexcept>

enum class State {
    IDLE,        // Clock is idle, not set or not ringing
    SET,         // Clock is being set to the desired time
    ALARM,       // Alarm ringing
    SNOOZE       // Snooze mode activated
};

class AlarmClockFSM {
private:
    State currentState;
    std::string time; // Simple representation of time in 24-hour format (HH:MM)
    bool alarmTriggered;

    // Helper function to validate time format
    bool isValidTime(const std::string& time) {
        if (time.length() != 5 || time[2] != ':') return false;
        int hours = std::stoi(time.substr(0, 2));
        int minutes = std::stoi(time.substr(3, 2));
        return (hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60);
    }

public:
    AlarmClockFSM() : currentState(State::IDLE), time("00:00"), alarmTriggered(false) {}

    // Start setting the clock
    void setTime(const std::string& newTime) {
        if (!isValidTime(newTime)) {
            throw std::invalid_argument("Invalid time format. Expected HH:MM.");
        }
        if (currentState == State::IDLE) {
            currentState = State::SET;
            time = newTime;
            std::cout << "Time set to " << time << std::endl;
        } else {
            std::cout << "Clock is already in use!" << std::endl;
        }
    }

    // Simulate alarm triggering
    void triggerAlarm() {
        if (currentState == State::SET) {
            currentState = State::ALARM;
            alarmTriggered = true;
            std::cout << "Alarm triggered! Time is " << time << std::endl;
        } else {
            std::cout << "Cannot trigger alarm while not set!" << std::endl;
        }
    }

    // Snooze functionality
    void snooze() {
        if (currentState == State::ALARM) {
            currentState = State::SNOOZE;
            std::cout << "Snooze activated! Alarm snoozed for 5 minutes." << std::endl;
            std::this_thread::sleep_for(std::chrono::minutes(5));
            currentState = State::ALARM;
            std::cout << "Snooze over. Alarm ringing again!" << std::endl;
        } else {
            std::cout << "No alarm to snooze!" << std::endl;
        }
    }

    // Stop the alarm and return to idle
    void stopAlarm() {
        if (currentState == State::ALARM || currentState == State::SNOOZE) {
            currentState = State::IDLE;
            alarmTriggered = false;
            std::cout << "Alarm stopped. Clock is idle now." << std::endl;
        } else {
            std::cout << "No alarm to stop!" << std::endl;
        }
    }

    // Display current state
    void showState() {
        std::cout << "Current State: ";
        switch (currentState) {
            case State::IDLE:
                std::cout << "IDLE (Clock is not set or alarm stopped)" << std::endl;
                break;
            case State::SET:
                std::cout << "SET (Clock is set to " << time << ")" << std::endl;
                break;
            case State::ALARM:
                std::cout << "ALARM (Alarm is ringing at " << time << ")" << std::endl;
                break;
            case State::SNOOZE:
                std::cout << "SNOOZE (Alarm is snoozed for 5 minutes)" << std::endl;
                break;
        }
    }
};

int main() {
    AlarmClockFSM alarmClock;

    // Example of using the AlarmClockFSM
    alarmClock.showState();  // Initial state

    alarmClock.setTime("07:00");  // Set alarm to 7:00 AM
    alarmClock.showState();  // After setting the time

    alarmClock.triggerAlarm();  // Trigger alarm
    alarmClock.showState();  // After alarm is triggered

    alarmClock.snooze();  // Activate snooze
    alarmClock.showState();  // After snooze ends

    alarmClock.stopAlarm();  // Stop the alarm and return to idle
    alarmClock.showState();  // After stopping the alarm

    return 0;
}