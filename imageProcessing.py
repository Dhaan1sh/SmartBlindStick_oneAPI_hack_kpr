import time
import RPi.GPIO as GPIO
from picamera2 import Picamera2
import cv2
import torch
import pyttsx3
import numpy as np

engine = pyttsx3.init()
engine.setProperty('rate', 150)
engine.setProperty('volume', 1.0)

model = torch.hub.load('ultralytics/yolov5:v6.2', 'yolov5s', pretrained=True)

picam2 = Picamera2()
picam2.configure(picam2.create_preview_configuration(main={"size": (640, 480)}))
picam2.start()

GPIO.setmode(GPIO.BCM)
TRIG_PIN = 23
ECHO_PIN = 24
GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)

def measure_distance():
    GPIO.output(TRIG_PIN, True)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, False)

    while GPIO.input(ECHO_PIN) == 0:
        start_time = time.time()

    while GPIO.input(ECHO_PIN) == 1:
        end_time = time.time()

    duration = end_time - start_time
    distance = (duration * 34300) / 2
    return distance

try:
    while True:
        frame = picam2.capture_array()
        results = model(frame)

        frame_center_x = frame.shape[1] // 2
        tolerance = 100

        obstacle_detected = False
        for *box, conf, cls in results.xyxy[0]:
            if conf > 0.25:
                x1, y1, x2, y2 = map(int, box)
                center_x = (x1 + x2) // 2
                label = f'{model.names[int(cls)]}: {conf:.2f}'

                if frame_center_x - tolerance < center_x < frame_center_x + tolerance:
                    distance = measure_distance()
                    if distance < 50:
                        command = f"Warning! {model.names[int(cls)]} detected in front, at a distance of {int(distance)} cm."
                        print(command)
                        obstacle_detected = True
                        engine.say(command)
                        engine.runAndWait()

                cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 0, 0), 2)
                cv2.putText(frame, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)

        if not obstacle_detected:
            print("No obstacle in front.")

        cv2.imshow('YOLOv5 Object Detection', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    picam2.stop()
    GPIO.cleanup()
    cv2.destroyAllWindows()
