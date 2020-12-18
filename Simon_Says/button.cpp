#include "button.h"

Button::Button(qreal size, int ord, bool inter) : ordinal(ord), size(size), isInteractive(inter)
{
    this->setRect(0, 0, size, size);
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    inter ? eff->setOpacity(1.0) : eff->setOpacity(0.0);
    this->setGraphicsEffect(eff);

    isPressed = false;
    isHovered = false;
    setAcceptHoverEvents(true);
    setFlag(ItemIsSelectable);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen borderPen;
    borderPen.setWidth(0);

    if(isInteractive) {
        if(isPressed)
        {
            painter->setBrush(QBrush(Qt::darkRed));
        }
        else
        {
            if(isHovered)
                painter->setBrush(QBrush(Qt::lightGray));
            else
                painter->setBrush(QBrush(Qt::gray));
        }
    }
    else {
        borderPen.setColor(Qt::darkRed);
        painter->setBrush(QBrush(Qt::darkRed));
    }

    painter->setPen(borderPen);
    painter->drawRect(this->rect());
}

QPropertyAnimation *Button::animateDiode(int duration)
{
    QPropertyAnimation *anim = new QPropertyAnimation(this->graphicsEffect(), "opacity", this);
    anim->setDuration(duration);
    anim->setKeyValueAt(0.0, 0.0);
    anim->setKeyValueAt(0.5, 1.0);
    anim->setKeyValueAt(1.0, 0.0);

    return anim;
}

void Button::setSize(qreal size)
{
    this->size = size;
}

int Button::getSize()
{
    return size;
}

int Button::getOrdinal()
{
    return ordinal;
}

void Button::setInteractive()
{
    isInteractive = !isInteractive;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(isInteractive){
        isPressed = true;
        update();
        QGraphicsItem::mousePressEvent(e);
    }
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if(isInteractive){
        isPressed = false;
        update();
        QGraphicsItem::mouseReleaseEvent(e);
        emit buttonPressed(ordinal);
    }
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    isHovered = true;
    QGraphicsItem::hoverEnterEvent(e);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    isHovered = false;
    QGraphicsItem::hoverLeaveEvent(e);
}
