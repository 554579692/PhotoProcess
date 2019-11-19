#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include<QMessageBox>
#include "opencv2/opencv.hpp"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include "Histogram.h"
#include "qcustomplot.h"
#include "image.h"
#include <string>
#include<iostream>
using namespace cv;
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ImageDefault.load("D:\\imageprocess\\default.png");
    ui->label->setPixmap(QPixmap::fromImage(ImageDefault));
    ImageProcess=ImageDefault;
    //ui->label->setScaledContents(true);
    //ui->label->resize(ui->widget->size());
    connect(ui->actiondakai, SIGNAL(triggered(bool)), this, SLOT(OpenImage())); //打开
    connect(ui->actioncunchu, SIGNAL(triggered(bool)), this, SLOT(SaveImage()));//存储
    connect(ui->actioncunchuwei, SIGNAL(triggered(bool)), this, SLOT(Saveas()));//存储为
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(huisezhifangtu())); //
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(junhenghua()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::zhifangtu(Histogram histogram)
{

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
        while(ui->label->width()>=1920||ui->label->height()>=1080)
        {
            ui->label->resize(QSize(int(ui->label->width()*0.9),int(ui->label->height()*0.9)));
        }
        img=img.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label->setPixmap(QPixmap::fromImage(img));
        ImageProcess=img;
        huisezhifangtu(filename.toStdString());
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

void MainWindow::junhenghua()
{
    cv::Mat srcImage=imread("C://Users//55457//Desktop//test.png");
    cv::imshow("BEFORE",srcImage);
    cv::Mat dstImage;
    Image x;
    dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//效果图的大小、类型与原图片相同
    double time0=static_cast<double>(getTickCount());
    x.togrey(srcImage,dstImage,32);//调用颜色空间缩减函数
    imshow("AFTER",dstImage);
}
void MainWindow::huisezhifangtu(string filename)
{
        Mat src,gray;
        src=imread(filename);
        cvtColor(src,gray,CV_RGB2GRAY);
        int bins = 256;
        int hist_size[] = {bins};
        float range[] = { 0, 256 };
        const float* ranges[] = { range};
        MatND hist;
        int channels[] = {0};

        calcHist( &gray, 1, channels, Mat(), // do not use mask
            hist, 1, hist_size, ranges,
            true, // the histogram is uniform
            false );

        double max_val;
        minMaxLoc(hist, 0, &max_val, 0, 0);
        int scale = 2;
        int hist_height=256;
        Mat hist_img = Mat::zeros(hist_height,bins*scale, CV_8UC3);
        for(int i=0;i<bins;i++)
        {
            float bin_val = hist.at<float>(i);
            int intensity = cvRound(bin_val*hist_height/max_val);  //要绘制的高度
            rectangle(hist_img,Point(i*scale,hist_height-1),
                Point((i+1)*scale - 1, hist_height - intensity),
                CV_RGB(255,255,255));
        }
        QImage hists=Mat2QImage(hist_img);
        cout<<hists.height()<<" "<<hists.width()<<endl;
        int Owidth=hists.width(),Oheight=hists.height();
        hists=hists.scaled(Owidth/2,Oheight/2,Qt::KeepAspectRatio);
        ui->label_2->setPixmap(QPixmap::fromImage(hists));
        //imshow( "Source", src );
        //imshow( "Gray Histogram", hist_img );
}
void MainWindow::zhifangtucanshu(std::string filename)//直方图参数
{
    Mat src,gray;
    src=imread(filename);
    cvtColor(src,gray,CV_RGB2GRAY);
    int bins = 256;
    int hist_size[] = {bins};
    float range[] = { 0, 256 };
    const float* ranges[] = { range};
    for(int i=0;i<gray.col();i++)
    {

    }
}
QImage MainWindow::Mat2QImage(cv::Mat cvImg)//Mat转Qimage
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
