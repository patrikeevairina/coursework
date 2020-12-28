#include "generator.h"

Generator::Generator(CustomScene *parent, Widget *widget, int level)
{
    QVector<QVector<int>> vector = decodeLocation(level);
    for (int i = 0; i < numCols; i++)
    {
        for (int j = 0; j < numRows; j++)
        {
            switch (vector[i][j])
            {
                case 1: {
                    Wall *newItem = new Wall();
                    parent->addItem(newItem);
                    parent->level.append(newItem);
                    newItem->setPos(i*cellWidth, j*cellHeight);
                    break;
                }
                case 2: {
                    Enemy *newEnemy = new Enemy(parent->first_item, widget);
                    parent->addItem(newEnemy);
                    parent->level.append(newEnemy);
                    newEnemy->setPos(i*cellWidth, j*cellHeight);
                    break;
                }
                case 3: {
                    Artefact *a = new Artefact();
                    parent->targetArtifacts++;
                    parent->addItem(a);
                    parent->level.append(a);
                    a->setPos(i*cellWidth, j*cellHeight);
                    break;
                }
                case 4:
                    parent->first_item->setPos(i*cellWidth, j*cellHeight);
                    break;
            }
        }
    }
}

QVector<QVector<int>> Generator::decodeLocation(int level)
{
    QFile file(QString(":/levels/%1").arg(level));
    file.open(QIODevice::ReadOnly);
    QTextStream arr(&file);

    cellWidth = arr.readLine().toInt();
    cellHeight = cellWidth;

    auto l = arr.readLine();
    file.close();

    numCols = width / cellWidth;
    numRows = height / cellHeight;

    QVector<QVector<int>> vector;

    int count = 0;
    for (int i = 0; i < numCols; i++)
    {
        QVector<int> q;
        for (int j = 0; j < numRows; j++)
        {
            q.push_back(l[count].digitValue());
            count++;
        }
        vector.push_back(q);
    }

    return vector;
}
