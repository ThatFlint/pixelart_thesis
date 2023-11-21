#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "drawspace.h"

DrawSpace::DrawSpace(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    drawing = false;
    myPenColor1 = Qt::black;
    myPenColor2 = Qt::white;
    myPenSize = 1;
}

bool DrawSpace::openImage(const QString &fileName){
    QImage loadedImage;
    if(!loadedImage.load(fileName)){
        return false;
    }
    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool DrawSpace::saveImage(const QString &fileName, const char *fileFormat){
    QImage visibleImage = image;
//    resize(&visibleImage, size());
    if(visibleImage.save(fileName, fileFormat)){
        modified = false;
        return true;
    } else {
        return false;
    }
}

void DrawSpace::setPenColor1(const QColor &newColor){
    myPenColor1 = newColor;
}

void DrawSpace::setPenColor2(const QColor &newColor){
    myPenColor2 = newColor;
}

void DrawSpace::setPenSize(int &newSize){
    myPenSize = newSize;
}

void DrawSpace::clearImage(){
    image.fill(qRgba(0,0,0,0));
    modified = true;
    update();
}

void DrawSpace::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton){
        drawing = true;
    }
}

void DrawSpace::mouseMoveEvent(QMouseEvent *event){
    if((event->button() == Qt::LeftButton || event->button() == Qt::RightButton) && drawing){
        drawLineTo(event->pos());
    }
}

void DrawSpace::mouseReleaseEvent(QMouseEvent *event){
    if((event->button() == Qt::LeftButton || event->button() == Qt::RightButton) && drawing){
        drawLineTo(event->pos());
        drawing = false;
    }
}

void DrawSpace::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect,image,dirtyRect);
}

void DrawSpace::resizeEvent(QResizeEvent *event){
    if(width() > image.width() || height() > image.height()){
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
}

void DrawSpace::drawLineTo(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor1, myPenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;
    int rad = (myPenSize / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void DrawSpace::resizeImage(QImage *image, const QSize &newSize){
    if(image->size() == newSize){
        return;
    }
    QImage newImage(newSize, QImage::Format_ARGB32);
    newImage.fill(qRgba(255,255,255,0));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *image);
    *image = newImage;
}


















