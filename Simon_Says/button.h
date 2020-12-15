#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Button(qreal size, int ord = 0, bool inter = true);
    // QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPropertyAnimation *animateDiode(int duration);

    void setSize(qreal size);
    void setInteractive();
    int getSize();
    int getOrdinal();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *e);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *e);

signals:
    void buttonPressed(int i);

private:
    int ordinal;
    qreal size;
    bool isInteractive;
    bool isPressed;
    bool isHovered;
};

#endif // BUTTON_H
