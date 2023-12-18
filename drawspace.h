#ifndef DRAWSPACE_H
#define DRAWSPACE_H

#include<QColor>
#include<QImage>
#include<QPoint>
#include<QWidget>

class Layer;

class DrawSpace : public QWidget
{
    Q_OBJECT

public:
    DrawSpace(QWidget *parent = 0);
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor1(const QColor &newColor);
    void setPenColor2(const QColor &newColor);
    void setPenSize(int &newSize);
    void setTool(QString &newTool);
    void resetLayers();

    bool isModified() const {return modified;}
    QColor penColor1() const {return myPenColor1;}
    QColor penColor2() const {return myPenColor2;}
    int penSize() const {return myPenSize;}

public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:

private:
    Layer *editingLayer;
    std::list<Layer> layers;
    Layer *selectedLayer;

    void drawLineTo(const QPoint &endPoint);
    void projectLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void clearTopLayer();
    bool modified;
    bool drawing;
    QColor myPenColor1;
    QColor myPenColor2;
    int myPenSize;
    QPoint lastPoint;
    QString tool;
    QString mode;


};
#endif // DRAWSPACE_H
