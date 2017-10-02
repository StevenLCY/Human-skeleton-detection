#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QImage"
#include "QFile"
#include "QTextStream"
#include "QFileDialog"
#include "QMessageBox"
#include "QMainWindow"
#include "opencv.hpp"
#include "QDebug"
#include "QSlider"
#include "QPushButton"
using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<cv::Mat>("cv::Mat");

    c = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}
QImage MainWindow::Mat2QImage(const cv::Mat src){
    if(src.type()==CV_8UC1)
    {
        QVector<QRgb> colorTable;
        for(int i=0;i<256;i++){
            colorTable.push_back(qRgb(i,i,i));
        }
        const uchar *qImageBuffer = (const uchar*)src.data;
        QImage img(qImageBuffer,src.cols,src.rows,src.step,QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }

    if(src.type()==CV_8UC3)
    {
        const uchar *qImageBuffer = (const uchar*)src.data;
        QImage img(qImageBuffer,src.cols,src.rows,src.step,QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "Error! Can't convert image type.";
        return QImage();
    }
}

void MainWindow::showImage(const cv::Mat &src)
{

    cv::Mat dst;
    int width = ui->loadImage->width();
    int height = ui->loadImage->height();
    double ratio = (double)width/(double)height;
    double imgRatio = src.cols/src.rows;

    if(ratio<imgRatio)
    {
        cv::resize(src,dst,cv::Size(width,(src.rows*width)/src.cols));
    }
    else
    {
        cv::resize(src,dst,cv::Size((src.cols*height)/src.rows,height));
    }
    ui->loadImage->setPixmap(QPixmap::fromImage(this->Mat2QImage(dst)));

}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    if(c)
    {
        c->stopCam();
        disconnect(c, SIGNAL(sendFrame(cv::Mat)), this, SLOT(getFrame(cv::Mat)));
        c->deleteLater();
    }
}

void MainWindow::on_action_Camera_triggered()
{
    if(ui->action_Camera->isChecked())
    {
        c = new camera();
        connect(c, SIGNAL(sendFrame(cv::Mat)), this, SLOT(getFrame(cv::Mat)));
        c->start();
    }
    else
    {
        c->stopCam();
    }
}

void MainWindow::getFrame(cv::Mat dst)
{
    //cv::imshow("ya", dst);
    cv::resize(dst, dst, cv::Size(ui->loadImage->width(), ui->loadImage->height()));
//    ui->loadImage->setPixmap(QPixmap::fromImage(QImage(dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888).rgbSwapped()));
    showImage(dst);
}
