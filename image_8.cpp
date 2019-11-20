#include "image_8.h"
#include "ui_image_8.h"
#include "opencv2/opencv.hpp"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;
image_8::image_8(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::image_8)
{
    ui->setupUi(this);
    LastFilename="test.jpg";
}

image_8::~image_8()
{
    delete ui;
    cout<<"??"<<endl;
}

void image_8::lianghua()  //量化演示
{
    Mat src,gray;
    src=imread(LastFilename.toStdString());
    cvtColor(src,gray,CV_RGB2GRAY);

    QImage image=Mat2QImage(gray);
    image=image.scaled(ui->label->size(), Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->setAlignment(Qt::AlignCenter);

    QImage image2=Mat2QImage(gray);
    image2=image2.scaled(ui->label_2->size(), Qt::KeepAspectRatio);
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
    ui->label_2->setAlignment(Qt::AlignCenter);

    QImage image3=Mat2QImage(gray);
    image3=image3.scaled(ui->label_3->size(), Qt::KeepAspectRatio);
    ui->label_3->setPixmap(QPixmap::fromImage(image3));
    ui->label_3->setAlignment(Qt::AlignCenter);

    QImage image4=Mat2QImage(gray);
    image4=image4.scaled(ui->label_4->size(), Qt::KeepAspectRatio);
    ui->label_4->setPixmap(QPixmap::fromImage(image4));
    ui->label_4->setAlignment(Qt::AlignCenter);

    QImage image5=Mat2QImage(gray);
    image5=image5.scaled(ui->label_5->size(), Qt::KeepAspectRatio);
    ui->label_5->setPixmap(QPixmap::fromImage(image5));
    ui->label_5->setAlignment(Qt::AlignCenter);

    QImage image6=Mat2QImage(gray);
    image6=image6.scaled(ui->label_6->size(), Qt::KeepAspectRatio);
    ui->label_6->setPixmap(QPixmap::fromImage(image6));
    ui->label_6->setAlignment(Qt::AlignCenter);

    QImage image7=Mat2QImage(gray);
    image7=image7.scaled(ui->label_7->size(), Qt::KeepAspectRatio);
    ui->label_7->setPixmap(QPixmap::fromImage(image7));
    ui->label_7->setAlignment(Qt::AlignCenter);

    QImage image8=Mat2QImage(gray);
    image8=image8.scaled(ui->label_8->size(), Qt::KeepAspectRatio);
    ui->label_8->setPixmap(QPixmap::fromImage(image8));
    ui->label_8->setAlignment(Qt::AlignCenter);

    //设置显示的文字
    ui->label_17->setText("量化演示");
    ui->label_17->setAlignment(Qt::AlignCenter);
    ui->label_9->setText("256");
    ui->label_9->setAlignment(Qt::AlignCenter);
    ui->label_10->setText("128");
    ui->label_10->setAlignment(Qt::AlignCenter);
    ui->label_11->setText("64");
    ui->label_11->setAlignment(Qt::AlignCenter);
    ui->label_12->setText("32");
    ui->label_12->setAlignment(Qt::AlignCenter);
    ui->label_13->setText("16");
    ui->label_13->setAlignment(Qt::AlignCenter);
    ui->label_14->setText("8");
    ui->label_14->setAlignment(Qt::AlignCenter);
    ui->label_15->setText("4");
    ui->label_15->setAlignment(Qt::AlignCenter);
    ui->label_16->setText("2");
    ui->label_16->setAlignment(Qt::AlignCenter);

}

void image_8::caiyang()    //采样演示
{
    Mat src,gray;
    src=imread(LastFilename.toStdString());
    cvtColor(src,gray,CV_RGB2GRAY);
}

void image_8::erzhihua()  //二值化演示
{
    Mat src,gray;
    src=imread(LastFilename.toStdString());
    cvtColor(src,gray,CV_RGB2GRAY);
}

void image_8::bmp2txt()  //bmp2txt演示
{

}

QImage image_8::Mat2QImage(cv::Mat cvImg)//Mat转Qimage
{
    QImage qImg;
    if (cvImg.channels() == 3)                             //三通道彩色图像
    {

        cv::cvtColor(cvImg, cvImg, CV_BGR2RGB);
        qImg = QImage((const unsigned char*)(cvImg.data),	cvImg.cols, cvImg.rows,	cvImg.cols*cvImg.channels(),QImage::Format_RGB888);
    }
    else if (cvImg.channels() == 1)                    //单通道（灰度图）
    {
        qImg = QImage((const unsigned char*)(cvImg.data),cvImg.cols, cvImg.rows,cvImg.cols*cvImg.channels(),QImage::Format_Indexed8);

        QVector<QRgb> colorTable;
        for (int k = 0; k<256; ++k)
        {
            colorTable.push_back(qRgb(k, k, k));
        }
        qImg.setColorTable(colorTable);//把qImg的颜色按像素点的颜色给设置
    }
    else
    {
        qImg = QImage((const unsigned char*)(cvImg.data),cvImg.cols, cvImg.rows,cvImg.cols*cvImg.channels(),QImage::Format_RGB888);
    }

    return qImg;

}
