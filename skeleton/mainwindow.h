#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "camera.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Camera_triggered();
    void closeEvent(QCloseEvent *);

    void getFrame(cv::Mat dst);

private:
    Ui::MainWindow *ui;
    QString fileName;
    cv::Mat mat;
    std::vector<cv::Mat> bgr_planes;
    camera *c;
    QImage Mat2QImage(const cv::Mat src);
    void MainWindow::showImage(const cv::Mat &src);
};

#endif // MAINWINDOW_H
