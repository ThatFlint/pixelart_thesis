#ifndef CANVAS_CONTAINER_H
#define CANVAS_CONTAINER_H

#include<QColor>
#include<QImage>
#include<QPoint>
#include<QWidget>

class DrawSpace;

class CanvasContainer : public QWidget
{
    Q_OBJECT

public:
    CanvasContainer(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    DrawSpace *editingLayer;
    std::list<DrawSpace> *layers;
    DrawSpace *selectedLayer;
};

#endif // CANVAS_CONTAINER_H
