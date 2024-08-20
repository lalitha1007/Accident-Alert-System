# Accident-Alert-System
Accident Alert Sysytem - IOT Project

### Overview

The **Accident Alert System** is an IoT-based project designed to detect vehicular accidents and automatically send alert notifications to a predefined mobile number. The system uses an accelerometer to monitor sudden changes in motion and a GPS module to capture the vehicle's location coordinates. In case of a detected accident, the system sends an SMS containing the vehicle's GPS coordinates and speed, along with a link to Google Maps, to aid in quick response and assistance.

### Features

- **Real-time Accident Detection**: The system continuously monitors the vehicle's motion using an accelerometer, detecting significant changes that may indicate an accident.
- **GPS Location Tracking**: Captures the exact latitude and longitude of the vehicle’s location using a GPS module.
- **Automated SMS Alerts**: Automatically sends an SMS with the accident location, speed, and a Google Maps link to a predefined emergency contact number.
- **LCD Display**: Provides real-time status updates on the system's initialization, GPS readiness, and alert status.
- **Configurable Parameters**: Key parameters such as the mobile number for alerts and GPS coordinates are easily configurable.

### Components Used

- **Arduino**: Microcontroller used for processing data from the accelerometer and GPS, and controlling the SMS module.
- **Accelerometer (e.g., ADXL335)**: Monitors the vehicle's X, Y, and Z-axis acceleration to detect sudden impacts.
- **GPS Module**: Captures the geographical location of the vehicle.
- **GSM Module**: Sends SMS alerts to a predefined mobile number in case of an accident.
- **LCD Display**: Provides a user interface to display system status.

### How It Works

1. **System Initialization**: Upon powering up, the system initializes the GSM, GPS, and accelerometer modules. It also calibrates the accelerometer to establish baseline readings for X, Y, and Z axes.
   
2. **Monitoring**: The system continuously monitors the accelerometer for significant deviations from the baseline values, which may indicate an accident.

3. **Accident Detection**: If an impact is detected (i.e., acceleration values exceed the defined threshold), the system retrieves the current GPS coordinates and speed.

4. **Alert Notification**: An SMS alert is sent to the emergency contact number, containing the GPS coordinates and a Google Maps link to the accident location.

### Getting Started

1. **Hardware Setup**: Connect the accelerometer, GPS module, GSM module, and LCD display to the Arduino as per the wiring diagram (provided in the documentation).
   
2. **Software Setup**: Upload the provided Arduino sketch to the microcontroller.

3. **Configuration**: Update the predefined mobile number and any other parameters in the code as required.

4. **Testing**: Run the system in a controlled environment to ensure it correctly detects and reports accidents.

### Future Enhancements

- **Multiple Alert Contacts**: Extend the system to send alerts to multiple contacts.
- **Real-time Monitoring**: Integrate with a cloud-based service for real-time monitoring and data logging.
- **Battery Backup**: Add a battery backup to ensure the system works even when the vehicle power is cut off.

### Contributing

Contributions are welcome! Please fork this repository and submit a pull request with your enhancements or bug fixes.
