#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPair>
#include <QGraphicsRectItem>
#include <QThread>

#include "wall.h"
#include "customscene.h"
#include "enemy.h"
#include "artefact.h"
#include "widget.h"

class CustomScene;


class Generator
{

public:
    Generator(CustomScene *parent = 0, Widget *w = 0, int level = 1);
    QVector<QVector<int>> decodeLocation(int level = 1);

public:
    int cellWidth;
    int cellHeight;
    int width = 1280;
    int height = 720;
    int numCols;
    int numRows;


};

#endif // ITEM_H
