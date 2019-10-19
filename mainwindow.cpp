#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include<QMessageBox>
#include "opencv2/opencv.hpp"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include "Histogram.h"
using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ImageDefault.load("D:\\imageprocess\\default.png");
    ui->label->setPixmap(QPixmap::fromImage(ImageDefault));
    ImageProcess=ImageDefault;
    //ui->label->setScaledContents(true);
    ui->label->resize(ui->widget->size());



    connect(ui->actiondakai, SIGNAL(triggered(bool)), this, SLOT(OpenImage()));
    connect(ui->actioncunchu, SIGNAL(triggered(bool)), this, SLOT(SaveImage()));
    connect(ui->actioncunchuwei, SIGNAL(triggered(bool)), this, SLOT(Saveas()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(lianghua()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(caiyang()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::OpenImage() //打开文件
{

    QString filename=QFileDialog::getOpenFileName( this,tr("open image file"),
                                                   "./",tr("Image files(*.bmp *.jpg *.pbm *.png *.ppm *.xbm *.xpm);;All files(*.*)"));
    if(filename.isEmpty())
        return;
    else
    {
        QImage img;
        if(!(img.load(filename))) //加载图像
        {
            QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
            return;
        }
        LastFilename=filename;
        ui->label->resize(ui->widget->size());
        ui->label->resize(QSize(img.width(),img.height()));
        while(ui->label->width()>=1920||ui->label->height()>=1080)
        {
            ui->label->resize(QSize(int(ui->label->width()*0.9),int(ui->label->height()*0.9)));
        }
        ui->label->setPixmap(QPixmap::fromImage(img.scaled(ui->label->size())));
        ImageProcess=img;
        //ui->label->setPixmap(QPixmap::fromImage(img));

        //加载直方图
//        Mat mat =imread(LastFilename.toStdString());
//        Mat calc=calcGrayHist(mat);
//        QImage qcalc=mat2qim(calc);
//        ui->label_2->resize(QSize(qcalc.width(),qcalc.height()));
//        ui->label_2->setPixmap(QPixmap::fromImage(qcalc.scaled(ui->label->size())));

//        Mat his = imread(LastFilename.toStdString(), 0);
//        Mat dst;
//        Histogram hist;
//        hist.getHist(his, dst);
//        hist.paintHist(dst, true);
          Histogram histogram;
          Mat mat=histogram.calcGray(LastFilename.toStdString());
          //cv::imshow("hi", mat);
          QImage qcalc=mat2qim(mat);
//        ui->label_2->resize(QSize(qcalc.width(),qcalc.height()));
          ui->label_2->setPixmap(QPixmap::fromImage(qcalc.scaled(ui->label_2->size())));



    }
}

void MainWindow::SaveImage()//存储文件
{
    if(ImageDefault==ImageProcess)
        return;
    else {
        ImageProcess.save(LastFilename);
    }
}

void MainWindow::Saveas() //存储为
{
    if(ImageDefault==ImageProcess)
        return;
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,tr("Open File"),"/",tr("Image files(*.bmp *.jpg *.pbm *.png *.ppm *.xbm *.xpm);;All files(*.*)"));
    if(fileName == "")
    {
        return;
    }
    ImageProcess.save(fileName);
}

void MainWindow::lianghua()  //量化演示
{

}

void MainWindow::caiyang()    //采样演示
{

}


QImage MainWindow::mat2qim(Mat &src)   //Mat to QImage
{
    //CV_8UC1 8位无符号的单通道---灰度图片
        if(src.type() == CV_8UC1)
        {
            //使用给定的大小和格式构造图像
            //QImage(int width, int height, Format format)
            QImage qImage(src.cols,src.rows,QImage::Format_Indexed8);
            //扩展颜色表的颜色数目
            qImage.setColorCount(256);

            //在给定的索引设置颜色
            for(int i = 0; i < 256; i ++)
            {
                //得到一个黑白图
                qImage.setColor(i,qRgb(i,i,i));
            }
            //复制输入图像,data数据段的首地址
            uchar *pSrc = src.data;
            //
            for(int row = 0; row < src.rows; row ++)
            {
                //遍历像素指针
                uchar *pDest = qImage.scanLine(row);
                //从源src所指的内存地址的起始位置开始拷贝n个
                //字节到目标dest所指的内存地址的起始位置中
                memcmp(pDest,pSrc,src.cols);
                //图像层像素地址
                pSrc += src.step;
            }
            return qImage;
        }
        //为3通道的彩色图片
        else if(src.type() == CV_8UC3)
        {
            //得到图像的的首地址
            const uchar *pSrc = (const uchar*)src.data;
            //以src构造图片
            QImage qImage(pSrc,src.cols,src.rows,src.step,QImage::Format_RGB888);
            //在不改变实际图像数据的条件下，交换红蓝通道
            return qImage.rgbSwapped();
        }
        //四通道图片，带Alpha通道的RGB彩色图像
        else if(src.type() == CV_8UC4)
        {
            const uchar *pSrc = (const uchar*)src.data;
            QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
            //返回图像的子区域作为一个新图像
            return qImage.copy();
        }
        else
        {
            return QImage();
        }
}
