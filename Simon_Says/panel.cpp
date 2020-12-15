#include "panel.h"

void Panel::resizeEvent(QResizeEvent *e)
{
    fitInView(this->scene()->sceneRect(), Qt::KeepAspectRatio);
}
