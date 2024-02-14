#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//qt includes
#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>

//local include
#include "facedetector.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class represents the main window of the application.
 *
 * This class manages the graphical user interface, video capturing, and face detection processes.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow object.
     *
     * Initializes the user interface, FaceDetector instance, and necessary components.
     *
     * @param parent The parent widget (default is nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object, releasing resources.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Captures video frames from the camera, performs face detection, and displays the result.
     *
     * This method is connected to a QTimer and is called at regular intervals to continuously update the displayed video feed.
     */
    void capturing();

    /**
     * @brief Stops the video capturing process and releases the camera.
     *
     * This method is triggered when the "Stop" button is clicked.
     */
    void on_stop_clicked();

    /**
     * @brief Starts the video capturing process, connecting the capturing slot to a QTimer.
     *
     * This method is triggered when the "Start" button is clicked.
     */
    void on_start_clicked();

private:
    Ui::MainWindow      *ui;              ///< The user interface for the main window.
    cv::VideoCapture    m_capture;        ///< Video capture object for accessing the camera.
    cv::Mat             m_frame;          ///< Current video frame captured from the camera.
    FaceDetector        m_detector;       ///< Face detection functionality encapsulated in a FaceDetector instance.
    QPixmap             *m_pixmap;        ///< QPixmap for displaying the processed video frame.
    QTimer              *m_intervalTimer; ///< Timer for triggering the capturing process at regular interval
    QGraphicsScene      *m_scene;         ///< QGraphicsScene for displaying the video feed in a QGraphicsView.
};

#endif // MAINWINDOW_H
