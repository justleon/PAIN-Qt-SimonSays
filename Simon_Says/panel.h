#ifndef PANEL_H
#define PANEL_H

#include <QGraphicsView>
#include <QResizeEvent>
#include "panelbuttons.h"

class Panel : public QGraphicsView
{
public:
    Panel(QWidget *parent) { };
    void resizeEvent(QResizeEvent *e);

};

#endif // PANEL_H
