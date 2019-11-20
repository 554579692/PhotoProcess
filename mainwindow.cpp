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
#include <sstream>
#include<iostream>
#include"image_8.h"
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
    image_8 lianghua_ui;
    //ui->label->setScaledContents(true);
    //ui->label->resize(ui->widget->size());
    connect(ui->actiondakai, SIGNAL(triggered(bool)), this, SLOT(OpenImage())); //打开
    connect(ui->actioncunchu, SIGNAL(triggered(bool)), this, SLOT(SaveImage()));//存储
    connect(ui->actioncunchuwei, SIGNAL(triggered(bool)), this, SLOT(Saveas()));//存储为
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(caiyang())); //采样率
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(lianghua())); //量化
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(erzhihua())); //二值化
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(bmp2txt())); //bmp2txt

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
        ui->label->setAlignment(Qt::AlignCenter);
        ImageProcess=img;
        huisezhifangtu(filename.toStdString());
        zhifangtucanshu(filename.toStdString());
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
    if(!LastFilename.isNull())
    lianghua_ui.LastFilename=LastFilename;
    lianghua_ui.lianghua();
    lianghua_ui.show();
}

void MainWindow::caiyang()    //采样演示
{
    if(!LastFilename.isNull())
    lianghua_ui.LastFilename=LastFilename;
    lianghua_ui.caiyang();
    lianghua_ui.show();
}

void MainWindow::erzhihua()  //二值化演示
{
    if(!LastFilename.isNull())
    lianghua_ui.LastFilename=LastFilename;
    lianghua_ui.erzhihua();
    lianghua_ui.show();
}

void MainWindow::bmp2txt()  //bmp2txt演示
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
        ui->label_2->setAlignment(Qt::AlignCenter);
        //imshow( "Source", src );
        //imshow( "Gray Histogram", hist_img );
}
void MainWindow::zhifangtucanshu(std::string filename)//直方图参数
{
    Mat src,gray;
    src=imread(filename);
    cvtColor(src,gray,CV_RGB2GRAY);
    int height=gray.rows;
    int width=gray.cols;
    //灰度图矩阵的长宽
    int huidu[256]; //灰度图的统计数组
    for(int i=0;i<256;i++) huidu[i]=0;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            int index=i*width+j;
            int data=(int)gray.data[index];
            huidu[data]++;
        }
    }
    int pixles=0;//像素总数
    double mean=0; //平均数
    double fangcha;//方差
    double std_dev;//标准差
    int median;//中间值

    for(int i=0;i<256;i++)
    {
        pixles+=huidu[i];
    }
    cout<<"Pixles="<<pixles<<endl;//像素总数

    for(int i=0;i<256;i++)
    {
        mean+=huidu[i]*(i+1);
    }
    mean/=pixles;
    cout<<"Mean="<<mean<<endl;//平均灰度

    for (int i=0;i<256;i++)
    {
        fangcha+=pow(huidu[i]-mean,2);
    }
    fangcha/=256;
    std_dev=sqrt(fangcha);
    cout<<"Std_dev="<<std_dev<<endl;//标准差
    int x=0;
    for(int i=0;i<256;i++)
    {
        x+=huidu[i];
        if(x>=pixles/2)
        {
            median=i;
            break;
        }
    }
    cout<<"Median="<<median<<endl;//中间值

    //将内容显示到控件上
    QString zhifangtu_info;
    zhifangtu_info="Mean: "+QString::number(mean, 10, 4)+"\nStd_dev: "+QString::number(std_dev, 10, 4)+"\nMedian: "+QString::number(median, 10, 4)+"\nPixels: "+QString::number(pixles, 10)+"\n";
    //zhifangtu_info<<"Mean: "<<mean<<endl<<"Std_dev: "<<std_dev<<endl<<"Median: "<<median<<endl<<"Pixels: "<<endl;
    //string zft_info;
    //zhifangtu_info>>zft_info;
    ui->label_3->setText(zhifangtu_info);
    ui->label_3->setAlignment(Qt::AlignCenter);

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
