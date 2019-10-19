#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

class Histogram
{
public:
    Histogram(void);
    ~Histogram(void);
    Mat calcGray(String filename);
    Mat calcH_s(String filename);
    Mat calcBGR(String filename);
private:
    String pingjunhuidu;   //平均灰度
    String zhongzhihuidu;  //中值灰度
    String biaozhuncha;    //标准差
    String xiangsuzongshu; //像素总数

};
