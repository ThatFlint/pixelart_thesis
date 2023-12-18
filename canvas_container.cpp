#include <string>
#include <iostream>
#include <QtWidgets>
#include "canvas_container.h"
#include "drawspace.h"

CanvasContainer::CanvasContainer(QWidget *parent) : QWidget(parent)
{
    editingLayer = new DrawSpace;
    DrawSpace firstLayer = new DrawSpace;
    layers = new std::list<DrawSpace>;
    layers->push_back(firstLayer);
    selectedLayer = &firstLayer;
}

