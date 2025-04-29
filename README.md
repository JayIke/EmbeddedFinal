# Embedded Systems Final Project
Arduino SONAR Object Detector with horizontal sweep and real-time display
## Features
Radar sweep: Horizontal sweep (270 degree sweep range, configurable) using a micro servo
GUI: Relative position and distance displayed real-time on OLED display
Object detection: SONAR via external ultrasonic sensor 
Control: Manual start/stop sweep button
## Hardware
Arduino Uno (ATMega328P uC), ultrasonic sensor (HC-SR04), OLED display (SSD1306), and micro servo (SG90).
## Protocol
I2c
### Summary
Object distance is measured by the time between sound wave transmission and reception from the ultrasonic sensor. The microcontroler, display, and sensor are fixed on top of the servo. The sonar sweep line is continuously displayed based on the radial position of the servo. Upon object detection, the display indicates the object with a circle marker and shows the distance calculated in cm.
### NOTE: Final/main2.c is the main file, not main.c
