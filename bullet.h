#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class bullet : public QObject, QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit bullet(QObject *parent = nullptr);

signals:

};

#endif // BULLET_H
