#include "camera.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
using namespace cv;
camera::camera(QObject *parent) :
    QThread(parent)
{
}

void camera::run()
{
    cv::VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())
        return;

    stopped = false;
    cv::Mat frame,frame2;

    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5));
    cv::waitKey(100);


    cv::VideoWriter w;
    Ptr<BackgroundSubtractor> pMOG;
    pMOG = cv::createBackgroundSubtractorMOG2();

    w.open("fugu.avi", cv::VideoWriter::fourcc('F', 'M', 'P', '4'), 30, cv::Size(cap.get(cv::CAP_PROP_FRAME_WIDTH), cap.get(cv::CAP_PROP_FRAME_HEIGHT)), true);

    cap >> frame;
    pMOG->apply(frame,frame2);

    while(!stopped)
    {
        cap >> frame;
//        cv::cvtColor(frame, frame, CV_BGR2GRAY);
//        cv::threshold(frame, frame , 100, 255, CV_THRESH_BINARY);
      GaussianBlur(frame,frame,Size(15,15),0);

        pMOG->apply(frame,frame2);
//        cv::cvtColor(frame2, frame2, CV_BGR2GRAY);
        cv::threshold(frame2, frame2 , 100, 255, CV_THRESH_BINARY);
        cv::morphologyEx(frame2, frame2, cv::MORPH_OPEN, element);

        cv::Mat skel(frame2.size(), CV_8UC1, cv::Scalar(0));
        cv::Mat temp(frame2.size(), CV_8UC1);
        bool done;
       do
        {
          cv::morphologyEx(frame2, temp, cv::MORPH_OPEN, element);
          cv::bitwise_not(temp, temp);
          cv::bitwise_and(frame2, temp, temp);
          cv::bitwise_or(skel, temp, skel);
          cv::erode(frame2, frame2, element);

          double max;
          cv::minMaxLoc(frame2, 0, &max);
          done = (max == 0);
        } while (!done);
       cv::dilate(skel, skel, element, cv::Point(-1,-1), 1);
//       cv::cvtColor(skel,skel,CV_GRAY2BGR);

       frame.setTo(Scalar(0,0,255),skel);

       emit sendFrame(frame);
       w.write(frame);
    }

    w.release();
}

