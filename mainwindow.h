#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "opencv2/opencv.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString LastFilename;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    cv::Mat calcGrayHist(const cv::Mat & image); //灰度直方图
    QImage mat2qim(cv::Mat &mat); //Mat to QImage
    cv::Mat qim2mat(QImage & qim); //QImage to Mat

private:
    Ui::MainWindow *ui;
    QImage ImageDefault;
    QImage ImageProcess;

public slots:
    void OpenImage();   //打开文件
    void SaveImage();   //存储文件
    void Saveas();      //存储为
    void caiyang();     //采样演示
    void lianghua();    //量化演示
    //void SaveasImage();

};
#endif // MAINWINDOW_H
