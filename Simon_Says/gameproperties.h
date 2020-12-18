#ifndef GAMEPROPERTIES_H
#define GAMEPROPERTIES_H

#include <QObject>
#include <QVector>
#include <QMessageBox>
#include <QSequentialAnimationGroup>
#include <QRandomGenerator>
#include "panelbuttons.h"

class GameProperties : public QObject
{
    Q_OBJECT

public:
    PanelButtons *AiButtons;
    PanelButtons *PlayerButtons;

    GameProperties();
    void animationClear();

    void setGamePlayed();
    void setPlayerTurn();

public slots:
    void aiTurn();
    void playerTurn(int i);
    void resetGame();

    void settingsChange(QVector<int> settings);

signals:
    void enablePlayerPanel(bool enable);
    void scoreUpdate(QString score);
    void comboUpdate(QString combo);
    void attemptsUpdate(QString lives);
    void gameEnded(bool gameEnded);
    void panelsChanged();

private:
    QSequentialAnimationGroup anim;
    QVector<int> AISequence;
    QVector<int> PlayerSequence;

    int boardSize = 3;
    int diodeLightUpTime = 750;
    int attempts = 3;
    int attemptsTaken = 0;
    qreal score = 0.0;
    qreal combo = 1.0;
    bool isGamePlayed = false;
    bool isPlayerTurn = false;
};

#endif // GAMEPROPERTIES_H
