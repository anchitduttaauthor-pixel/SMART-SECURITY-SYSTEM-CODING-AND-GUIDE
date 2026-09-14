AI AND ROBOTICS PROJECT 
SMART LOCKER SECURITY SYSTEM 
 
This is the manual for a smart locker security system that works with the help of an Ultrasonic Sensor and a 4x4 Matrix Keypad, combined with an Arduino Uno and a Passive Buzzer. This is a completely independent system that runs without the need of any human being.  
 
CORE PRINCIPLES: 
This system works depending on different situations given below: 
1. Password Protection: One of the most important security features of this system is that it is password protected. Only the ones knowing the correct password can use this without any problem. 
2. Authorized Access: If the correct password is entered, the system automatically disarms itself and lets the user do whatever they want. It automatically arms itself again after the door is closed. It starts a countdown of 10 seconds after the correct password is entered to ensure that if the user doesn’t open the door even after entering the correct password, it can rearm itself after 10 seconds. 
3. Wrong Password Entry: If any wrong password is entered, the Arduino turns ON the Passive Buzzer to make a loud sound and warn the intruder. It will not stop the buzzer until the correct password is entered. 
4. Unauthorized Break-In Attempt: If anyone opens the door without entering any password, the Arduino again turns on the Passive Buzzer as a warning. It will not stop until the door is closed or the correct password is entered. 
 
COMPONENTS REQUIRED: 
1. Ultrasonic Sensor (HC-SR04) 
2. 4x4 Matrix Keypad
3. Arduino Uno 
4.a) Passive Buzzer Module OR 4.b) Passive Buzzer  
5. Breadboard (Full Size) 
6.Jumper Wires 
  
(Note: In this project, in case of the passive buzzer, the normal (bare) passive buzzer is highly recommended rather than the module. Use the module if you want a very loud sound, but for normal projects, the bare one is best.) 


How It Works: 
The Ultrasonic Sensor in the box acts as the watcher. It sees the differences in the distance between the door and itself. So, if the door is opened, the distance increases, and it carries out its works accordingly. The Matrix Keypad acts as the keypad for password entry. It tells the Arduino if the correct password was entered. If the correct password is entered, the Arduino ignores the sensor signal and lets the user work. The keypad tells it if the wrong password was entered and it shoots the buzzer. If no password was entered, the sensor notices the difference in distance and tell the Arduino, after which, the Arduino turns on the buzzer.  
It is smart system designed to arm itself, disarm itself, and again rearm itself completely independently without any user input.  
 
WIRING GUIDE:

1. Arduino 5V-- Breadboard Positive Rail
           GND-- Breadboard Negative Rail

2. HC-SR04 VCC & GND-- Positive & Negative Rail
           TRIG & ECHO-- A1 & A2 (Analog Pins)

3. Passive Buzzer Positive-- Digital Pin 10
           GND/Negative-- Negative Rail

4. Keypad Pins 1-8-- Digital Pins 2-9

5. Passive Buzzer Module (If used instead):
    VCC & GND-- Positive & Negative Rail
    I/O-- Digital Pin 10






