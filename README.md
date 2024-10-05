# SmartBlindStick_oneAPI_hack_kpr
# Object Detection, Obstacle Warning, and GPS Tracking System

## Project Overview
This project is an object detection, obstacle warning, and GPS tracking system built using a Raspberry Pi 4, YOLOv5 for object detection, an ultrasonic sensor for distance measurement, and a GPS module for tracking location. The system detects objects in real-time using a camera and provides verbal warnings through a text-to-speech (TTS) engine if an obstacle is detected directly in front of the user. The ultrasonic sensor measures the distance to obstacles, and if an object is closer than 50 cm, a warning is issued.

Additionally, the system uses a GPS module to continuously track and log the user's location. This GPS data can be integrated with mapping services for real-time tracking or location-based functionalities.

This project aims to help users navigate safely in various environments by detecting obstacles in their path and providing information on their location.

## Table of Components

| Component                     | Description                                                   |
|-------------------------------|---------------------------------------------------------------|
| Raspberry Pi 4                | Main processing unit                                          |
| Picamera                      | Captures real-time video for object detection                |
| Ultrasonic Sensor (HC-SR04)   | Measures the distance to objects                              |
| GPS Module (Neo-6M)          | Provides location tracking through GPS                        |
| YOLOv5 Model                  | Pretrained model used for object detection                   |
| TTS Engine (pyttsx3)         | Provides audio warnings when objects are detected             |
| GPIO Pins                     | Used to interface the ultrasonic sensor and GPS with Raspberry Pi |
| Python Libraries               | OpenCV, torch, pyttsx3, RPi.GPIO, Picamera2, and GPS library for functionality |

## Pin Configuration

### Ultrasonic Sensor (HC-SR04)
The ultrasonic sensor is used for detecting the distance to objects:

| Sensor Pin | GPIO Pin on Raspberry Pi | Description                                  |
|------------|--------------------------|----------------------------------------------|
| VCC        | Pin 2 (5V)              | Power supply                                 |
| GND        | Pin 6 (Ground)          | Ground connection                            |
| TRIG       | GPIO 23 (Pin 16)        | Trigger pin for sending the ultrasonic pulse |
| ECHO       | GPIO 24 (Pin 18)        | Echo pin for receiving the reflected pulse   |

### GPS Module (Neo-6M)
The GPS module provides location data for tracking purposes:

| GPS Pin | GPIO Pin on Raspberry Pi | Description                                  |
|---------|--------------------------|----------------------------------------------|
| VCC     | Pin 4 (5V)              | Power supply                                 |
| GND     | Pin 6 (Ground)          | Ground connection                            |
| TX      | GPIO 15 (Pin 10)        | Transmit pin for sending GPS data to Raspberry Pi |
| RX      | GPIO 14 (Pin 8)         | Receive pin for receiving data from Raspberry Pi |

## Camera Configuration
The Raspberry Pi Camera is used with the Picamera2 library for video capture and processing. It connects to the camera port on the Raspberry Pi and streams video at a resolution of 640x480 pixels.

## Features
- **Object Detection:** Real-time object detection using the YOLOv5 model.
- **Obstacle Detection:** Measures the distance to objects using an ultrasonic sensor and provides warnings if objects are detected within 50 cm.
- **GPS Tracking:** Continuously tracks the user’s location using a GPS module and logs the coordinates for real-time tracking or location analysis.
- **Verbal Warnings:** Uses a TTS engine to provide voice alerts for obstacles and other relevant information.
- **Real-time Visualization:** Displays object detection results with bounding boxes on a live video stream.

## Getting Started

### Prerequisites
- Python 3.x
- Raspberry Pi 4 with Raspbian OS
- OpenCV
- PyTorch (for YOLOv5)
- pyttsx3 (for TTS)
- RPi.GPIO (for ultrasonic sensor)
- GPS library (such as gpsd or similar)
- Picamera2

### Installation
Clone this repository:

```bash
git clone https://github.com/yourusername/project-repo.git
cd project-repo
