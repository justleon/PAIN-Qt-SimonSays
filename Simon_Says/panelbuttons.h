#ifndef PANELBUTTONS_H
#define PANELBUTTONS_H

#include <QVector>
#include <QGraphicsScene>
#include "button.h"

class PanelButtons : public QGraphicsScene
{
public:
    PanelButtons(bool inter, int size, QObject *parent = Q_NULLPTR);
    void setUpPanel(int num);

    Button* getButton(int index);

private:
    QVector<Button*> buttons;
    bool isInteractive;
};

#endif // PANELBUTTONS_H
