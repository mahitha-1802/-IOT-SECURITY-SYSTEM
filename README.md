# -IOT-SECURITY-SYSTEM

*COMPANY*: CODTECH IT SOLUTIONS

*NAME*: MAHITHA GUDALA

*INTERN ID*: CT6WRPH

*DOMAIN*: INTERNET OF THINGS

*DURATION*: 6 WEEKS

*MENTOR*: NEELA SANTOSH

*DESCRIPTION*: 1. Components Needed:
Microcontroller: ESP32 or Raspberry Pi.

Motion Sensor: PIR (Passive Infrared) sensor.

Camera Module: Compatible with your microcontroller, e.g., ESP32-CAM.

Wi-Fi Module: Often built into modern microcontrollers like ESP32.

Power Supply: Ensure it's compatible with your chosen microcontroller and other components.

Mobile App: For receiving alerts.
2. System Architecture:
a. Motion Detection:
PIR Sensor: Detects motion and sends a signal to the microcontroller.

b. Image Capture:
Camera Module: Captures an image when motion is detected.

c. Alert System:
Microcontroller: Sends an alert to a predefined mobile app with the captured image.
3. Steps to Build the Prototype:
a. Setting Up the Microcontroller:
Install necessary development environment tools (Arduino IDE for ESP32, or Raspbian for Raspberry Pi).

Connect the PIR sensor to one of the digital input pins.

Connect the camera module to the respective pins (refer to the microcontroller's datasheet).

b. Programming the Microcontroller:
PIR Sensor Code: Write a simple program to detect motion and trigger the camera module.

Camera Module Code: Capture an image when motion is detected.

Wi-Fi Connection Code: Establish a connection to your Wi-Fi network.

Alert System Code: Send the captured image via an HTTP request to a mobile app server.

c. Developing the Mobile App:
Use platforms like Flutter, React Native, or native development tools.

Implement functionality to receive alerts and display images.

Set up backend services (Firebase, AWS) to handle and store incoming images and alerts.
4. Testing and Debugging:
Test each component individually: Ensure the PIR sensor detects motion, the camera captures images, and the microcontroller connects to Wi-Fi.

Integrate and test: Combine all components and test the system as a whole. Check for real-time alerts on the mobile app.

5. Finalizing the Prototype:
Securely mount the components in an enclosure.

Optimize the code for performance and reliability.

Ensure the mobile app runs smoothly and handles real-time alerts effectively.

6. Documentation:
Document the setup, code, and instructions for using the system

