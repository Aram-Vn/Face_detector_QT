#include "facedetector.h"
#include <QDebug>

FaceDetector::FaceDetector() :
    // Initialize the path to the Haar Cascade XML file
    m_cascade_name((QCoreApplication::applicationDirPath() + "/haarcascade_frontalface_default.xml").toStdString()),

    // Define a color for drawing rectangles around faces
    m_square_color { cv::Scalar(0.0, 0.0, 255.0)}
{
    // Load the face cascade classifier
    if(!m_face_cascade.load(m_cascade_name))
    {
        // Create a QString error message with a formatted string.
        // %1 in the string will be replaced with the converted m_cascade_name.
        QString errorMessage = QString("<---Error--->\nUnable to load the face cascade classifier\n"
                                       "Make sure the XML file is present at: %1").arg(QString::fromStdString(m_cascade_name));

        // Print the error message using qFatal.
        // qPrintable is used to convert the QString to a const char* for compatibility.
        qFatal("%s", qPrintable(errorMessage));
    }
}

QImage FaceDetector::detect(cv::Mat frame)
{
    // Convert the input frame to grayscale
    cv::Mat frame_gray;
    cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);

    // Equalize the histogram to improve contrast
    equalizeHist(frame_gray, frame_gray);

    // Perform face detection using the Haar Cascade classifier
    m_face_cascade.detectMultiScale(frame_gray,
                                    m_found_faces,
                                    1.1, 2, 0|cv::CASCADE_SCALE_IMAGE,
                                    cv::Size(100, 100));

    // hold the amount of detected faces
    size_t count_of_found_faces = m_found_faces.size();

    //for drawing rectangles around faces
    cv::Rect rect;

    // Iterate over each detected face in m_found_faces
    for(size_t i = 0; i < count_of_found_faces; i++)
    {
        // Retrieve the current detected face bounding box
        rect = m_found_faces[i];

        // Change the color of rectangles based on the index in m_square_colors
        // The color cycling is achieved using m_square_colors[i % m_square_colors.size()]
        rectangle(frame, cv::Point(rect.x, rect.y),
                  cv::Point((rect.x + rect.width),
                  (rect.y + rect.height)),
                  m_square_color, 2);
    }

    // Convert Mat to QImage
    QImage result = QImage((const uchar *)frame.data,
                           frame.cols,
                           frame.rows,
                           frame.step,
                           QImage::Format_RGB888).rgbSwapped();
    return result;
}
