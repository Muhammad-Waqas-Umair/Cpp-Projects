# FSM Alarm Clock in C++

This project implements a **Finite State Machine (FSM)** based alarm clock in C++. The FSM is used to manage different states of an alarm clock, such as setting the time, checking the time, and ringing the alarm. It showcases the use of a state machine to control the flow of the application based on user input.

## Features

- **IDLE**: The initial state where the alarm clock is waiting for user input.
- **SETTING_TIME**: A state where the user can set the time for the alarm.
- **ALARM_RINGING**: The alarm rings when the set time is reached.
- **TIME_DISPLAY**: Displays the current time.
  
## How It Works

The program defines a finite state machine that switches between different states based on the actions taken by the user. It handles:

- **Setting the time** for the alarm.
- **Displaying the current time**.
- **Ringing the alarm** when the time is reached.

The user can interact with the program by choosing different options in the terminal, which triggers transitions between states.


