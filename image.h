#ifndef IMAGE_H
#define IMAGE_H
#include<QImage>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

class Image:public QImage
{
public:
    Image();
    ~Image();
    QImage dianyunsuan1(QImage img);//点运算1
    QImage dianyunsuan2(QImage img);//点运算2
    QImage zhifangtujunheng(QImage img,int model);//直方图均衡功能,model是模式选项
    QImage kongjianbianhuan(QImage img);//空间变换
    QImage togrey(cv::Mat &inputImage,cv::Mat& outputImage,int div);//彩色图转灰色图
    QImage togrey(Image img,cv::Mat &inputImage,cv::Mat& outputImage,int div);//彩色图转灰度图,自身处理时使用


};

#endif // IMAGE_H
