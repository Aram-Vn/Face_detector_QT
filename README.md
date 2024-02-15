# OpenCV Face Detection Qt Application

## description
This is a simple Qt application that integrates OpenCV for face detection. The application captures video from a webcam, detects faces in each frame, and displays the video with rectangles around the detected faces.

## Features

- Face detection using the Haarcascade frontal face classifier from OpenCV.
- Real-time video capture and display.
- Integration of Qt for the graphical user interface.

---

> [!IMPORTANT]
> 
> ## Prerequisites
>
> Before running the application, ensure you have the following dependencies installed:
> 
> - [Qt](https://www.qt.io/) - Qt 5.x development environment
> - [OpenCV](https://opencv.org/) - library (version 4.x)
> - A C++ compiler (for Qt)
>
> ### OpenCV Include Path
> 
> Make sure to specify the correct path to the OpenCV headers in `Face_detector.pro`:
>
> ```pro
> # Specify include paths for OpenCV headers
> # Change the path if needed
> INCLUDEPATH += /usr/include/opencv4
> ```
> ### Haar Cascade XML File Path
> 
> The Haar Cascade XML file is used for face detection. Ensure the correct path is set in the `FaceDetector` constructor in `facedetector.cpp`:
> 
> ```cpp
> FaceDetector::FaceDetector() :
>    // Initialize the path to the Haar Cascade XML file
>    // !!_Change path if needed_!!
>    m_cascade_name("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml"),
> ```

---
## Getting Started

1. **Clone the Repository:**
   ```bash
   git clone git@github.com:Aram-Vn/Face_detector_QT.git # Clone the repository
    ```
2. **Build and Run:**
   ```bash
    cd Face_detector_QT # Navigate to the project directory
    qmake && make       # Build the Qt application
    ./Face_detector     # Run the Application
   ```

3. **Usage:**
   - Click the "Start" button to begin capturing video.
   - Detected faces will be highlighted with rectangles in real-time.
   - Click the "Stop" button to end the video capture.

## Project Structure

- **facedetector.cpp/h:** Contains the FaceDetector class responsible for face detection using OpenCV.
- **mainwindow.cpp/h:** Implements the main application window using Qt.
- **main.cpp:** Entry point for the application.
