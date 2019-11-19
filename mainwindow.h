#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "opencv2/opencv.hpp"
#include "histogram.h"
#include <string>
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
    QImage Mat2QImage(cv::Mat cvImg); //Mat to QImage
    cv::Mat QImage2Mat(QImage & qim); //QImage to Mat
    void zhifangtu(Histogram histogram);

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
    void junhenghua(); //均衡化演示
    void huisezhifangtu(std::string filename);//灰色直方图绘制
    void zhifangtucanshu(std::string filename);//直方图参数
    //void SaveasImage();

};
#endif // MAINWINDOW_H
