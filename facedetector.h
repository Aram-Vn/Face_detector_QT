#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

//opencv inculdes
// #include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"

//qt & C++ includes
#include <QImage>
#include <vector>

// using namespace cv;
/**
 * @brief The FaceDetector class encapsulates the face detection functionality using Haar Cascade classifier.
 *
 * This class provides methods to initialize the face cascade, perform face detection, and convert the processed frame to a QImage.
 */
class FaceDetector
{
public:
    /**
     * @brief Constructs a FaceDetector object.
     *
     * Initializes the path to the Haar Cascade XML file and loads the face cascade classifier.
     */
    FaceDetector(); // default constructor

public slots:
    /**
     * @brief Detect faces in the given frame and return the result as a QImage.
     *
     * This method converts the input frame to grayscale, equalizes the histogram,
     * performs face detection using Haar Cascade, draws rectangles around detected faces,
     * and converts the processed frame to a QImage.
     *
     * @param frame The input frame for face detection.
     * @return A QImage containing the processed frame with rectangles around detected faces.
     */
    QImage detect(cv::Mat frame);

private:
    cv::String                   m_cascade_name;   ///< Path to the Haar Cascade XML file.
    cv::CascadeClassifier        m_face_cascade;   ///< Cascade classifier for face detection.
    std::vector<cv::Rect>        m_found_faces;    ///< Vector to store the detected faces.
    cv::Scalar                   m_square_color;     ///< List of colors for drawing rectangles around faces.
};

#endif // FACEDETECTOR_H
