# Specify the required Qt modules
QT       += core gui multimedia multimediawidgets

# Include the 'widgets' module for versions greate
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Set C++ standard to C++17
CONFIG += c++17

#to access camera in mac
macx {
    QMAKE_INFO_PLIST = $$PWD/Info.plist.in
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Specify include paths for OpenCV headers
# change th path if needed

unix {
    INCLUDEPATH += /usr/include/opencv4 # posible path for unix
}

win32 {
    INCLUDEPATH += C:/opencv/build/install/include/opencv4 # posible path for windows
}

macx {
   INCLUDEPATH += /usr/local/include/opencv4 # posible path for mac
}

message(Qt version: $$[QT_VERSION])

# Specify library paths and link against OpenCV libraries
LIBS += -L/usr/local/lib \
        -lopencv_core \
        -lopencv_imgcodecs \
        -lopencv_highgui \
        -lopencv_imgproc \
        -lopencv_videoio \
        -lopencv_ml \
        -lopencv_video \
        -lopencv_features2d \
        -lopencv_calib3d \
        -lopencv_objdetect \
        -lopencv_flann

# List of source files for the project
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    facedetector.cpp \


# List of header files for the project
HEADERS += \
    mainwindow.h \
    facedetector.h

# List of UI forms for the project
FORMS += \
    mainwindow.ui


# Create the images directory in the build directory
QMAKE_POST_LINK += mkdir -p $$OUT_PWD/images

copydata.commands = $(COPY_DIR) $$PWD/cvFiles/haarcascade_frontalface_default.xml  $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
