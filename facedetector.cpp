#include "facedetector.h"
#include <QDebug>

FaceDetector::FaceDetector()
{
     // Initialize the path to the Haar Cascade XML file
    m_cascade_name = "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";

    // Load the face cascade classifier
    if(!m_face_cascade.load(m_cascade_name))
    {
        qDebug() << "--(!)Error loading\n";  // Print an error message if the classifier fails to load
    }


    // Define a collection of colors for drawing rectangles around faces
    /*8 colors collection*/
    m_colors_col  << cv::Scalar(0.0,0.0,255.0)   << cv::Scalar(0.0,128.0,255.0)
                  << cv::Scalar(0.0,255.0,255.0) << cv::Scalar(0.0,255.0,0.0)
                  << cv::Scalar(255.0,128.0,0.0) << cv::Scalar(255.0,255.0,0.0)
                  << cv::Scalar(255.0,0.0,0.0)   << cv::Scalar(255.0,0.0,255.0);
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

    size_t n = m_found_faces.size();

    //Draw rectangles around faces
    cv::Rect rect;

    for(size_t i = 0; i < n ; i++)
    {
        rect = m_found_faces[i];

        // Change the color of rectangles based on the index in m_colors_col
        // The color cycling is achieved using m_colors_col[i % 8]
        rectangle(frame, cv::Point(rect.x, rect.y),
                  cv::Point((rect.x + rect.width),
                  (rect.y + rect.height)),
                  m_colors_col[i%8]);
    }

    // Convert Mat to QImage
    QImage result = QImage((const uchar *)frame.data,
                           frame.cols,
                           frame.rows,
                           frame.step,
                           QImage::Format_RGB888).rgbSwapped();
    return result;
}

