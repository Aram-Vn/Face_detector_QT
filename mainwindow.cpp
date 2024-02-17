#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),              // Initialize the main window and set up the user interface
    m_detector(),                        // Create a FaceDetector instance
    m_intervalTimer(new QTimer(this)),   // Create a QTimer for continuous capturing
    m_pixmap(new QPixmap()),             // Create a QPixmap for displaying processed m_frames
    m_scene(new QGraphicsScene())        // Create a QGraphicsScene for displaying m_frames in the QGraphicsView
{
    ui->setupUi(this);  // Initialize the main window and set up the user interface
}


MainWindow::~MainWindow() // Release resources when the MainWindow is destroyed
{
    delete ui;
}


void MainWindow::capturing()
{
    m_capture.read(m_frame);                                  // Read a m_frame from the camera
    QImage result = m_detector.detect(m_frame);               // Perform face detection on the m_frame using the FaceDetector instance
    m_pixmap.reset(new QPixmap(QPixmap::fromImage(result)));  // Convert the result to a QPixmap for display

    m_scene.reset(new QGraphicsScene(ui->graphicsView));     // Create a new QGraphicsScene for the QGraphicsView
    m_scene->addPixmap(*m_pixmap);                           // Add the QPixmap to the m_scene
    m_scene->setSceneRect(m_pixmap->rect());                 // Set the m_scene rectangle to match the size of the QPixmap
    ui->graphicsView->setScene(m_scene.data());              // Set the QGraphicsView to display the m_scene
}

void MainWindow::on_start_clicked()
{
    // The Videom capture instance 'm_capture' is opened, capturing video from the default camera (index 0)
    m_capture.open(0); // Open the defoult camera


    // Connect the 'capturing' slot (capturing method) to the 'timeout' signal of the m_intervalTimer
    // This ensures that the capturing method will be called at regular intervals
    connect(m_intervalTimer.data(), &QTimer::timeout, this, &MainWindow::capturing);
    // Start the timer to m_capture frames at regular intervals (approximately 30 frames per second)

    // The m_intervalTimer is started with a timeout period of 33 milliseconds,
    // aiming to achieve a m_frame rate close to 30 m_frames per second (1000 ms / 33 ms ≈ 30 fps)
    m_intervalTimer->start(33);
}

void MainWindow::on_stop_clicked() // Stop the timer and disconnect the capturing slot
{
    // Stop the timer to prevent further timeouts
    m_intervalTimer->stop();

    // Disconnect the capturing slot (capturing method) from the timeout signal of the m_intervalTimer
    // This ensures that the capturing method won't be automatically called when the timer times out
    // It effectively stops the continuous capturing process
    disconnect(m_intervalTimer.data(), &QTimer::timeout, this, &MainWindow::capturing);

    // Release the camera resources
    m_capture.release();
}
