#include "image.h"
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

Image::Image()
{

}

Image::~Image()
{

}

QImage Image::togrey(cv::Mat &inputImage,cv::Mat& outputImage,int div)
{
    outputImage=inputImage.clone(); //复制实参到临时变量
    int rowNumber=outputImage.rows; //行数
    int colNumber=outputImage.cols*outputImage.channels(); //每行的元素个数=列数*通道数
    for(int i=0;i<rowNumber;i++)
    {
        uchar* data=outputImage.ptr<uchar>(i);
        for(int j=0;j<colNumber;j++)
        {
            data[j]=data[j]/div*div+div/2;
        }
    }
    QImage x;
    return x;
}
