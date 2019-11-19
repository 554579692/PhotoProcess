#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include<QString>
#include<QWidget>
#include <QImage>
#include "qcustomplot.h"
#include <opencv2/opencv.hpp>
class Histogram
{
public: 
    Histogram(QString filename);
    int pixels;  //像素总数
    int level;  //灰度级别
    int mean;  //平均值
    int median;//中间值
    int count;
    int percentile;
    QImage redraw(QString filename);
    QImage qimage;
    QCustomPlot *m_pChart;
private:

};

#endif // HISTOGRAM_H
