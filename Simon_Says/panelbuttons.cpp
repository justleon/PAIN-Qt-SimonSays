#include "panelbuttons.h"

#define DEFAULT_VAL 3

PanelButtons::PanelButtons(bool inter, int size, QObject *parent) : isInteractive(inter)
{
    setUpPanel(size);
}

void PanelButtons::setUpPanel(int num)
{
    int count = num;
    int size = 100 - (count - DEFAULT_VAL) * 25;
    int offset = 110 - (count - DEFAULT_VAL) * 20;

    buttons.clear();
    for(int i = 0; i < count; i++){
        for(int j = 0; j < count; j++){
            Button *n_button = new Button(size, (i * count) + j + 1, isInteractive);
            n_button->setPos(-50.0 + offset * j, -50.0 + offset * i);

            this->addItem(n_button);
            buttons.append(n_button);
        }
    }
}

Button *PanelButtons::getButton(int index)
{
    return buttons[index];
}
