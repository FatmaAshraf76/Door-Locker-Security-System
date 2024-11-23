# Door-Locker-Security-System
Dual Microcontroller-Based Door Locker Security System Using Password Authentication

Objective: 

The objective of this project is to develop a secure and efficient smart door control system. It 
uses two microcontrollers, HMI_ECU and Control_ECU, which communicate via UART. The 
system implements password authentication, stores data in external EEPROM, and integrates 
additional components such as a PIR sensor, H-bridge motor control, and a buzzer for 
enhanced functionality. 
 
Project Overview: 

This smart door control system is designed with two microcontrollers, one acting as the 
Human-Machine Interface (HMI_ECU) and the other as the Control Unit (Control_ECU). Users 
interact with the system using an LCD and keypad to enter passwords, which are verified and 
stored using external EEPROM. The door is controlled by an H-bridge circuit connected to a 
motor, and the system includes a PIR sensor for motion detection, a buzzer for alarms, and 
password-protected access to system options like door unlocking and password changing. 

Features: 

1. Password Protection: Users can set and verify a password stored in external EEPROM. 
2. LCD and Keypad Interface: Allows easy interaction for entering and managing passwords. 
3. UART Communication: HMI_ECU sends and receives data to and from Control_ECU via UART. 
4. EEPROM Storage: Passwords and system data are stored securely in an external EEPROM. 
5. Motorized Door Control: The door is unlocked/locked using a motor driven by an Hbridge. 
6. Buzzer Alert: The buzzer is activated for failed password attempts and system alerts. 
7. PIR Motion Sensor: Detects motion to trigger door operations. 
8. Password Change Option: Users can change the password after verification. 
9. Security Lock: System locks for one minute if the password is entered incorrectly three times consecutively. 
