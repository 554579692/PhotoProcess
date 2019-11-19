#include "histogram.h"
#include <QString>
#include <QImage>
#include <QVector>


Histogram::Histogram(QString filename)
{
    qimage=redraw(filename);
}

QImage Histogram::redraw(QString filename)
{
    QImage image(filename);
    if(!image.allGray())
    {
        image=image.convertToFormat(QImage::Format_Grayscale8);
    }
    if(!image.isNull())
    {
        int nWidth=image.width();
        int nHeight=image.height();
        QVector<double> vecX;
        QVector<double> vecY(256,0);

        int i=0;
        while(256!=i){
            vecX.append(i);
            ++i;
        }
        for (int j=0;j<nHeight;j++) {
            for (int k = 0;k<nWidth;k++) {
                int nIndex=int(image.bits()[j*nHeight+k]);
                vecY[nIndex]=vecY.at(nIndex)+1;
            }
        }

        double yMax=0;
        for(int j=0;j<256;j++)
        {
            if(yMax<vecY.at(j))
                yMax=vecY.at(j);
        }
        m_pChart->yAxis->setRange(0,yMax);
        m_pChart->graph(0)->setData(vecX,vecY);
                //    m_pChart->graph(0)->setPen(QPen(Qt::red));
                m_pChart->replot();

                //    qDebug() << "gray:" << image.bits();
                image.scaled(800,600,Qt::AspectRatioMode::KeepAspectRatio);
    }
    return image;
}
