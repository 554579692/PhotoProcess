#ifndef IMAGE_8_H
#define IMAGE_8_H

#include <QWidget>
#include "opencv2/opencv.hpp"
namespace Ui {
class image_8;
}

class image_8 : public QWidget
{
    Q_OBJECT

public:
    explicit image_8(QWidget *parent = nullptr);
    ~image_8();
    QString LastFilename;
    QImage Mat2QImage(cv::Mat cvImg); //Mat to QImage
    cv::Mat QImage2Mat(QImage & qim); //QImage to Mat

    void caiyang();     //采样演示
    void lianghua();    //量化演示
    void erzhihua();    //二值化演示
    void bmp2txt();     //bmp2txt演示

private:
    Ui::image_8 *ui;
};

#endif // IMAGE_8_H
