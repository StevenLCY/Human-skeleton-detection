#ifndef CAMERA_H
#define CAMERA_H

#define USE_FFMPEG
#include <QThread>
#include <opencv2/opencv.hpp>

class camera : public QThread
{
    Q_OBJECT
public:
    explicit camera(QObject *parent = 0);
    void run();
    void stopCam(){stopped = true;}

signals:
    void sendFrame(cv::Mat src);

public slots:
private:
    bool stopped = false;
};

#endif // CAMERA_H
